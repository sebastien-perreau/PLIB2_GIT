/*********************************************************************
 * 
 *	Section 31 - DMA modules (0 to 7)
 * 
 *	Author : Sebastien PERREAU
 *
 ********************************************************************/

#include "../PLIB2.h"

static dma_channel_registers_t * p_dma_channels_registers_array[] =
{
    (dma_channel_registers_t *) &DCH0CON,
    (dma_channel_registers_t *) &DCH1CON,
    (dma_channel_registers_t *) &DCH2CON,
    (dma_channel_registers_t *) &DCH3CON,
    (dma_channel_registers_t *) &DCH4CON,
    (dma_channel_registers_t *) &DCH5CON,
    (dma_channel_registers_t *) &DCH6CON,
    (dma_channel_registers_t *) &DCH7CON
};
static dma_event_handler_t dma_event_handler[DMA_NUMBER_OF_MODULES] = {NULL};
static bool dma_channel_is_using[DMA_NUMBER_OF_MODULES] = {0};

const uint8_t dma_irq[] = 
{
    _DMA0_IRQ,
    _DMA1_IRQ,
    _DMA2_IRQ,
    _DMA3_IRQ,
    _DMA4_IRQ,
    _DMA5_IRQ,
    _DMA6_IRQ,
    _DMA7_IRQ    
};

/*******************************************************************************
 * Function:
 *      static dma_module_type_t __dma_get_free_channel()
 *
 * Overview:
 *      This routine is used to get a free DMA channel. The first channel to be used
 *      is DMA0 and so on up to channel DMA7.    
 * 
 * Input:
 *      none
 * 
 * Output:
 *      The next free DMA channel.
 ******************************************************************************/
static dma_module_type_t __dma_get_free_channel()
{
    dma_module_type_t i;
    for (i = DMA0 ; i < DMA_NUMBER_OF_MODULES ; i++)
    {
        if (!dma_channel_is_using[i])
        {
            dma_channel_is_using[i] = true;
            break;
        }
    }
    if (i == DMA_NUMBER_OF_MODULES)
    {
        ERROR(__ERROR_DMA_NO_MORE_FREE_CHANNEL);
    }
    return i;
}

/*******************************************************************************
 * Function:
 *      dma_module_type_t dma_init( dma_event_handler_t evt_handler, 
 *                           dma_channel_control_type_t dma_channel_control,
 *                           dma_channel_interrupt_type_t dma_channel_interrupt,
 *                           dma_channel_event_type_t dma_channel_event,
 *                           uint8_t irq_num_tx_start,
 *                           uint8_t irq_num_tx_abord)
 *
 * Overview:
 *      This routine is used to initialize a DMA module.
 *   
 *      When using Pattern Match mode and a pattern is detected then a DMA_INT_BLOCK_TRANSFER_DONE
 *      is set. Interrupt can be handle (if enable) and the DMA channel behavior is the same
 *      as Block Transfer Complete (DMA_INT_BLOCK_TRANSFER_DONE flag is set and DMA channel is
 *      disable).
 *    
 *      Configure the DMA channel in AUTO_ENABLE mode allow the channel to be always ENABLE even 
 *      after a BLOCK_TRANSFER_DONE. Thus it is not necessary to re-configure the channel
 *      with the dma_set_transfer_params routine. 
 *
 * Input:
 *      evt_handler             - The handler (function) to call when an interruption occurs.
 *      dma_channel_control     - The DMA Channel Control Register (see dma_channel_control_type_t).
 *      dma_channel_interrupt   - The DMA Channel Interrupt Register (see dma_channel_interrupt_type_t).
 *                              It manages the type of interruption and is also used, in this routine,
 *                              to clear all channel flags.
 *      dma_channel_event       - The DMA Channel Event Register (see dma_channel_event_type_t). It is used
 *                              to setup the type of event for start transfer, abord transfer and/or 
 *                              pattern match abord.
 *      irq_num_tx_start        - The IRQ number for start event transfer (e.i: _UART1_TX_IRQ).
 *      irq_num_tx_abord        - The IRQ number for abord event transfer (e.i: _TIMER_1_IRQ).
 * 
 * Output:
 *      It returns the DMA channel which has been initialized (DMA0..DMA7).
 ******************************************************************************/
dma_module_type_t dma_init( dma_event_handler_t evt_handler, 
                            dma_channel_control_type_t dma_channel_control,
                            dma_channel_interrupt_type_t dma_channel_interrupt,
                            dma_channel_event_type_t dma_channel_event,
                            uint8_t irq_num_tx_start,
                            uint8_t irq_num_tx_abord)
{   
    dma_module_type_t id = __dma_get_free_channel();
    
    dma_channel_is_using[id] = true;
    
    dma_event_handler[id] = evt_handler;
    irq_init(IRQ_DMA0 + id, (evt_handler != NULL) ? IRQ_ENABLED : IRQ_DISABLED, irq_dma_priority(id));
    
    // Enable the DMA controller
    DMACONSET = _DMACON_ON_MASK;
    // Abord all current operations on the DMA module.
    dma_abord_transfer(id);
    // Set DMA Channel Control Register
    p_dma_channels_registers_array[id]->DCHCON = (dma_channel_control & ~DMA_CONT_CHANNEL_ENABLE);
    // Set DMA Channel Event Control Register
    p_dma_channels_registers_array[id]->DCHECON = dma_channel_event | (irq_num_tx_start << _DCH0ECON_CHSIRQ_POSITION) | (irq_num_tx_abord << _DCH0ECON_CHAIRQ_POSITION);
    // Set DMA Channel Interrupt Control Register
    p_dma_channels_registers_array[id]->DCHINTCLR = DMA_INT_ALL;
    p_dma_channels_registers_array[id]->DCHINTSET = (dma_channel_interrupt & 0x00ff0000);
        
    return id;
}

/*******************************************************************************
 * Function:
 *      uint32_t dma_suspend()
 * 
 * Description:
 *      The function suspends the DMA controller.
 * 
 *      Note: After the execution of this function the DMA operation is supposed 
 *      to be suspended. I.e. the function has to wait for the suspension to take place!
 * 
 * Parameters:
 *      none
 * 
 * Return:
 *      true if the DMA was previously suspended, false otherwise
 ******************************************************************************/
uint32_t dma_suspend()
{
    uint32_t previous_dma_status;
    if (!(previous_dma_status = DMACONbits.SUSPEND))
    {
        DMACONSET = _DMACON_SUSPEND_MASK;   // suspend
        while((DMACONbits.DMABUSY));        // wait to be actually suspended
    }
    return previous_dma_status;
}

/*******************************************************************************
 * Function:
 *      void dma_resume(uint32_t suspend_status)
 * 
 * Description:
 *      The function restores the DMA controller activity to the old suspended mode.
 * 
 * Parameters:
 *      suspend_status      - The desired DMA suspended state.
 * 
 * Return:
 *      none
 ******************************************************************************/
void dma_resume(uint32_t suspend_status)
{
    if (!suspend_status)
    {
        DMACONCLR = _DMACON_SUSPEND_MASK;	// resume DMA activity
    }
    else
    {
        dma_suspend();
    }
}

/*******************************************************************************
 * Function:
 *      void dma_set_channel_event_control(dma_module_type_t id, dma_channel_event_type_t dma_channel_event)
 *
 * Description:
 *      This routine is used to set the channel event control of a DMA module. This setup is
 *      first called in the dma_init routine at the initialization but in your program you may
 *      want to modify this setup at a specific time. You can thus modify this setup whenever 
 *      you want thanks to this routine.
 *
 * Parameters:
 *      id                      - The DMA module you want to use.
 *      dma_channel_event       - The DMA Channel Event Register (see dma_channel_event_type_t). It is used
 *                              to setup the type of event for start transfer, abord transfer and/or 
 *                              pattern match abord.
 * 
 * Return:
 *      none
 ******************************************************************************/
void dma_set_channel_event_control(dma_module_type_t id, dma_channel_event_type_t dma_channel_event)
{
    dma_abord_transfer(id);
    
    p_dma_channels_registers_array[id]->DCHECONCLR = DMA_EVT_START_TRANSFER_ON_IRQ | DMA_EVT_ABORD_TRANSFER | DMA_EVT_ABORD_TRANSFER_ON_PATTERN_MATCH;
    p_dma_channels_registers_array[id]->DCHECON |= dma_channel_event;
}

/*******************************************************************************
 * Function:
 *      void dma_set_transfer_params(dma_module_type_t id, dma_channel_transfer_t * channel_transfer)
 *
 * Description:
 *      This routine is used to configure a transfer. It setup all pointers, sizes and
 *      pattern require by the DMA channel for a transfer. It also enable the channel
 *      (it needs to be disable in order to modify the channel registers) and can
 *      force the first cell block transfer.
 *
 *      The source and destination pointers can be either RAM content or SFR registers. 
 *      The sizes source, destination and cell are maximum DMA_MAX_TRANSFER_SIZE.
 *      The pattern (for pattern match mode) can be either 1 or 2 bytes length (it 
 *      depends of the configuration in dma_init(... dma_channel_control ...)).
 *
 * Parameters:
 *      id                  - The DMA module you want to use.
 *      channel_transfer*   - The pointer of dma_channel_transfer_t containing all data 
 *                          require by the DMA channel to initialize a transfer. 
 * 
 * Return:
 *      none
 *   
 * IMPORTANT:
 *      If START_TRANSFER_ON_IRQ and/or ABORD_TRANSFER_ON_IRQ and/or DMA_EVT_ABORD_TRANSFER_ON_PATTERN_MATCH are used by 
 *      the DMA channel with a TX irq source (such as UART Tx, SPI Tx...) then WHEN the DMA module is ENABLED, the transmission
 *      AUTOMATICALLY and IMMEDIATELY started (no need to force the transfer). This is normal because we want 
 *      to generate a DMA transfer when the Tx pin is ready to send something.
 *      On the other hand if the irq source is something like Rx pin, a timer or any other event then the 
 *      DMA transfer will occurs ONLY when the trigger appears. We can force the transfer if we want
 *      but it is useless.
 * 
 *      If we DO NOT use any events to generate a DMA transfer (RAM to RAM copy by example) then we are oblige
 *      to force the DMA transfer.
 ******************************************************************************/
void dma_set_transfer_params(dma_module_type_t id, dma_channel_transfer_t * channel_transfer)
{
    dma_channel_enable(id, OFF, false);
    while (dma_channel_is_enable(id));
    p_dma_channels_registers_array[id]->DCHSSA = _VirtToPhys(channel_transfer->src_start_addr);
    p_dma_channels_registers_array[id]->DCHDSA = _VirtToPhys(channel_transfer->dst_start_addr);
    p_dma_channels_registers_array[id]->DCHSSIZ = channel_transfer->src_size;
    p_dma_channels_registers_array[id]->DCHDSIZ = channel_transfer->dst_size;
    p_dma_channels_registers_array[id]->DCHCSIZ = channel_transfer->cell_size;
    p_dma_channels_registers_array[id]->DCHDAT = channel_transfer->pattern_data;    
    p_dma_channels_registers_array[id]->DCHINTCLR = DMA_FLAG_ALL;
}

/*******************************************************************************
 * Function:
 *      void dma_channel_enable(dma_module_type_t id, bool enable, bool force_transfer)
 *
 * Description:
 *      This routine is used to enable or disable a DMA channel.
 *
 * Parameters:
 *      id                  - The DMA module you want to use.
 *      enable              - A boolean value (1: enable, 0: disable).
 *      force_transfer      - This flag is used to force a DMA transmission (for example if the DMA module is configure 
 *                          in "DMA_EVT_NONE" to trigger the transfer or simply if the user want to have a transfer without
 *                          to wait any event(s). This flag is ignored if the DMA module is configured with at least one of the
 *                          three events type (START / ABORD / ABORD ON PATTERN) AND the IRQ source is a PERIPHERAL with TX 
 *                          (see note in dma_set_transfer_params)
 * 
 * Return:
 *      none
 ******************************************************************************/
void dma_channel_enable(dma_module_type_t id, bool enable, bool force_transfer)
{
    (enable) ? (p_dma_channels_registers_array[id]->DCHCONSET = DMA_CONT_CHANNEL_ENABLE) : (p_dma_channels_registers_array[id]->DCHCONCLR = DMA_CONT_CHANNEL_ENABLE);
    (force_transfer) ? (p_dma_channels_registers_array[id]->DCHECONSET = DMA_EVT_FORCE_TRANSFER) : (p_dma_channels_registers_array[id]->DCHECONCLR = DMA_EVT_FORCE_TRANSFER);
}

/*******************************************************************************
 * Function:
 *      void dma_abord_transfer(dma_module_type_t id)
 *
 * Description:
 *      This routine is used to abord the transfer on a DMA channel. It turns off
 *      the channel, clear the source and destination pointers, and reset the event
 *      detector. When an abord transfer is requested, the current transaction in
 *      progress (if any) will complete before the channel is reset. 
 *      The channel registers can be modify only while the channel is disabled.
 *
 * Parameters:
 *      id          - The DMA module you want to use.
 * 
 * Return:
 *      none
 ******************************************************************************/
void dma_abord_transfer(dma_module_type_t id)
{
    p_dma_channels_registers_array[id]->DCHECONSET = DMA_EVT_ABORD_TRANSFER;
    while ((p_dma_channels_registers_array[id]->DCHECON & DMA_EVT_ABORD_TRANSFER) > 0);
}

/*******************************************************************************
 * Function:
 *      bool dma_channel_is_enable(dma_module_type_t id)
 *
 * Description:
 *      This routine is used to know if the DMA channel is enabled.
 *
 * Parameters:
 *      id          - The DMA module you want to use.
 * 
 * Return:
 *      true if enable, false otherwise.
 ******************************************************************************/
bool dma_channel_is_enable(dma_module_type_t id)
{
    return ((p_dma_channels_registers_array[id]->DCHCON & DMA_CONT_CHANNEL_ENABLE) > 0) ? 1 : 0;    
}

/*******************************************************************************
 * Function:
 *      uint16_t dma_get_index_cell_pointer(dma_module_type_t id)
 *
 * Description:
 *      This routine is used to get the current index of the cell pointer. When a
 *      DMA transmission occurs, the data is moved from A to B (A & B are memory area).
 *      Sometimes you know how many bytes are transfered and sometimes not (for example
 *      you setup your DMA module to ABORD a transmission on a PATTERN_MATCH). Whit this 
 *      routine you can get the last index of the DMA module when the ABORD occurs. 
 *      (Example: You setup your DMA module to receive up to 1000 bytes of a UART module,
 *      and add an abord condition on a pattern_match - 8 or 16 bits - then if the pattern
 *      is detected on the UART RX then the abord condition occurs - DMA_INT_BLOCK_TRANSFER_DONE
 *      flag is set - and the DMA module is aborded. How many bytes have been received (including
 *      the pattern ? Use this routine to have the answer).
 *
 * Parameters:
 *      id          - The DMA module you want to use.
 * 
 * Return:
 *      The pointer index of the cell.
 ******************************************************************************/
uint16_t dma_get_index_cell_pointer(dma_module_type_t id)
{
    return (uint16_t) p_dma_channels_registers_array[id]->DCHCPTR;
}

/*******************************************************************************
 * Function:
 *      dma_channel_flags_type_t dma_get_flags(dma_module_type_t id)
 *
 * Description:
 *      This routine is used to get all the flags (see dma_channel_flags_type_t) of a DMA
 *      channel. There are up to 8 types of interruption by DMA channel (so up to 
 *      8 different flags).
 *      You can use flags without to enable interruption. Just check and handle
 *      flags when you want.
 *
 * Parameters:
 *      id          - The DMA module you want to use.
 * 
 * Return:
 *      The channel flags status.
 ******************************************************************************/
dma_channel_flags_type_t dma_get_flags(dma_module_type_t id)
{
    dma_channel_flags_type_t flags = (p_dma_channels_registers_array[id]->DCHINT) & 0xff;
    return flags;
}

/*******************************************************************************
 * Function:
 *      void dma_clear_flags(dma_module_type_t id, dma_channel_flags_type_t flags)
 *
 * Description:
 *      This routine is used to clear flag(s) of a DMA channel (see dma_channel_flags_type_t).
 *
 * Parameters:
 *      id          - The DMA module you want to use.
 *      flags       - The flag(s) you want to clear (see dma_channel_flags_type_t).
 * 
 * Return:
 *      none
 ******************************************************************************/
void dma_clear_flags(dma_module_type_t id, dma_channel_flags_type_t flags)
{
    p_dma_channels_registers_array[id]->DCHINTCLR = flags;
}

/*******************************************************************************
 * Function: 
 *      const uint8_t dma_get_irq(dma_module_type_t id)
 * 
 * Description:
 *      This routine is used to get the IRQ number of a DMA module.
 * 
 * Parameters:
 *      id: The DMA module you want to use.
 * 
 * Return:
 *      The constant IRQ number.
 ******************************************************************************/
const uint8_t dma_get_irq(dma_module_type_t id)
{
    return dma_irq[id];
}

/*******************************************************************************
 * Function:
 *      void dma_interrupt_handler(dma_module_type_t id)
 *
 * Description:
 *      This routine is called when an interruption occurs. This interrupt 
 *      handler calls the user _event_handler (if existing) otherwise do nothing.
 *
 * Parameters:
 *      id          - The DMA module you want to use.
 * 
 * Return:
 *      none
 ******************************************************************************/
void dma_interrupt_handler(dma_module_type_t id)
{
    if (dma_event_handler[id] != NULL)
    {
        dma_channel_flags_type_t flags = (p_dma_channels_registers_array[id]->DCHINT) & 0xff;
        (*dma_event_handler[id])(id, flags);
    }
}



static dma_crc_t __crc = {0};
static uint32_t __crc_dummy = 0x00000000;
static dma_module_type_t __dma_crc_id = 0;
static dma_channel_transfer_t __dma_crc_ch_transfer = {NULL, &__crc.__value, 0, 0, 0, 0x0000};

static uint32_t __crc_non_direct_seed(uint32_t seed, uint32_t polynomial, uint8_t polynomial_order)
{
    uint8_t lsb;
    uint32_t msb_mask = (1 << (polynomial_order - 1));
    
    while (polynomial_order-- > 0)
    {
        lsb = seed & 1;
        if (lsb) 
        {
            seed ^= polynomial;
        }
        seed >>= 1;
        if (lsb)
        {
            seed |= msb_mask;
        }
    }
    return seed;
}

static uint32_t __crc_reflect_data(uint32_t data, uint8_t data_bit_length)
{
    uint32_t reflection = 0;
    uint8_t current_bit;
    for (current_bit = 0; current_bit < data_bit_length; ++current_bit)
    {
        if (data & 0x01)
        {
            reflection |= (1 << ((data_bit_length - 1) - current_bit));
        }
        data >>= 1;
    }
    return reflection;
}

static void __crc_event_handler(uint8_t id, dma_channel_flags_type_t flags)
{
    if ((flags & DMA_FLAG_BLOCK_TRANSFER_DONE) > 0)
    {
        dma_clear_flags(id, DMA_FLAG_BLOCK_TRANSFER_DONE); 
        
        if (__crc.__evt_state == 1)
        {
            dma_crc_execute(&__crc_dummy, (__crc.polynomial_order / 8));
        }
        else
        { 
            if (__crc.reflected_io)
            {
                __crc.__value = __crc_reflect_data(__crc.__value, __crc.polynomial_order);
            }
            __crc.__is_updated = true;
            __crc.__evt_state = 0;
            DCRCDATA = __crc.seed;
        }
    }
}

void dma_crc_init(uint32_t polynomial_value, uint8_t polynomial_order, uint32_t seed, bool reflected_io, uint32_t xorout)
{
    __dma_crc_id = dma_init(  __crc_event_handler, 
                            DMA_CONT_PRIO_3, 
                            DMA_INT_BLOCK_TRANSFER_DONE, 
                            DMA_EVT_NONE, 
                            0xff, 
                            0xff);
     
    __crc.polynomial_value = polynomial_value;
    __crc.polynomial_order = polynomial_order;
    __crc.seed = __crc_non_direct_seed(seed, polynomial_value, polynomial_order);
    __crc.reflected_io = reflected_io;
    __crc.xorout = xorout;
    
    __crc.__value = 0;
    __crc.__evt_state = 0;
    __crc.__is_updated = false;
    
    DCRCCON = 0;
    DCRCXOR = __crc.polynomial_value;
    DCRCDATA = __crc.seed;
    DCRCCON = (__crc.reflected_io ? DMA_CRC_CALCULATED_LSB_FIRST : DMA_CRC_CALCULATED_MSB_FIRST) | ((__crc.polynomial_order - 1) << 8) | DMA_CRC_CON_ENABLE | DMA_CRC_CON_APPEND_ENABLE | DMA_CRC_CON_TYPE_LFSR | __dma_crc_id;   
}

void dma_crc_execute(void * p_data, uint32_t length)
{
    __dma_crc_ch_transfer.src_start_addr = p_data;
    __dma_crc_ch_transfer.src_size = length;
    __dma_crc_ch_transfer.dst_size = length;
    __dma_crc_ch_transfer.cell_size = length;
    
    dma_set_transfer_params(__dma_crc_id, &__dma_crc_ch_transfer);  
    dma_channel_enable(__dma_crc_id, ON, true);     // Force the transfer because no EVENT (DMA_EVT_NONE) has been set on __dma_crc_id.
    
    __crc.__evt_state++;
}

bool dma_crc_is_calculated(uint32_t * p_crc)
{
    if (__crc.__is_updated)
    {
        __crc.__is_updated = false;
        *p_crc = __crc.__value;
        return true;
    }
    return false;
}
