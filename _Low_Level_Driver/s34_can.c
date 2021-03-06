/*********************************************************************
 * 
 *	Section 34 - CAN modules (1 and 2)
 * 
 *	Author : Sebastien PERREAU
 * 
 *  Note:
 *  -----
 *  Bit Rate (kb/s)     Bus Length (m)
 *      1000                30
 *      500                 100
 *      250                 250
 *      125                 500
 * 
 ********************************************************************/

#include "../PLIB2.h"

#warning "s34_can.c - Maximum of 32 Tx frames & 32 Rx frames (automatic filter for Rx)"

static can_registers_t * p_can_registers_array[] =
{
    (can_registers_t *) &C1CON,
    (can_registers_t *) &C2CON
};

static can_params_t * p_can_params[CAN_NUMBER_OF_MODULES];

/*******************************************************************************
 * Function:
 *      static void __can_set_op_mode(CAN_MODULE id, CAN_OP_MODE op_mode)
 * 
 * Overview:
 *      This function is used to enter in one of the different operation mode available. 
 *      The CAN module can operate in one of the following modes selected by the user application:
 *          - Configuration mode
 *          - Normal Operation mode
 *          - Listen-Only mode
 *          - Listen All Messages mode
 *          - Loopback mode
 *          - Disable mode
 * 
 * Input:
 *      id          - The CAN module to use
 *      op_mode     - The operation mode requested (see can_con_reg_t.REQOP for more details)
 * 
 * Output:
 *      none
 ******************************************************************************/
static void __can_set_op_mode(CAN_MODULE id, CAN_OP_MODE op_mode)
{
    p_can_registers_array[id]->CANCON.REQOP = op_mode;
    while (p_can_registers_array[id]->CANCON.OPMOD != op_mode);
}

/*******************************************************************************
 * Function:
 *      static void __can_set_speed(CAN_MODULE id, CAN_BUS_SPEED bus_speed, bool set_auto_bit_timing)
 * 
 * Overview:
 *      This function set the CxCFG register (used for the bus bit timing).
 *      
 *      Informations:
 *       -------------
 *      1: SEG2PH <= (PRSEG + SEG1PH). If SEG2PHTS is clear, SEG2PH will be set automatically.
 *         More the BUS_SPEED is and more the PRSEG value should be (ex. 1Tq pour 125KBPS, 7Tq pour 1MBPS).
 *      2: 3 Time bit sampling is not allowed for BRP < 2.
 *      3: SJW < SEG2PH. (The Synchronization Jump Width (SJW) adjusts the bit clock as necessary by 1 - 4TQ (as configured) to maintain synchronization with the transmitted message)
 *      4: The CAN Nominal Bit Time 'N' = SYNC_SEG (1Tq) + PRSEG (1Tq..8Tq) + SEG1PH (1Tq..8Tq) + SEG2PH (1Tq..8Tq) should be between [8 .. 25].
 *      5: The sample point is the point in a CAN bit time interval where the sample is taken and the bus state is read and interpreted. 
 *         It is situated between Phase Segment 1 and Phase Segment 2 (around 75% of the CAN Nominal Bit Time). The CAN bus can be sampled once or thrice at the sample point, as configured by the Sample CAN Bus Line (SAM).
 * 
 *      How to calculate (example):
 *      ---------------------------
 *          - SYSTEM_FREQUENCY = 48 MHz
 *          - BUS_SPEED = 500 KBPS
 *      1. BRP = ((SYSTEM_FREQUENCY / (2 x BUS_SPEED x N)) - 1) The BRP value should be an integer.
 *      2. In order to have an integer BRP value, we choose the CAN Nominal Bit Time 'N' (which is between [8 .. 25]) as follow N = 12
 *      3. With N = 12, BRP = 3. Because BRP > 1, we can set the SAM bit (3 Time bit sampling).
 *      4. N = SYNC_SEG (1Tq) + PRSEG (1Tq..8Tq) + SEG1PH (1Tq..8Tq) + SEG2PH (1Tq..8Tq) = 12
 *          4.1.    We are looking for a sample point around 75%. 75% de N -> 9Tq. So SEG2PH = 12 - 9 = 3Tq (=2)
 *          4.2.    Based on system characteristics, we choose a propagation delay of 3Tq -> PRSEG = 3Tq (=2)
 *          4.3.    N = 1Tq + 3Tq + SEG1PH + 3Tq -> SEG1PH = 12 - 1 - 3 - 3 = 5Tq (=4) we respect the relation SEG2PH <= (PRSEG + SEG1PH)
 *      5. Because SJW < SEG2PH, we choose SJW = 2Tq (=1)
 *      6. Parameters are: BRP = 3, SEG2PH = 2, SEG1PH = 4, PRSEG = 2, SJW = 1, SAM = 1    
 * 
 * Input:
 *      id                      - The CAN module to use
 *      bus_speed               - The CAN bus speed (125KBPS / 250KBPS / 500KBPS or 1MBPS)
 *      set_auto_bit_timing     - Set this flag if you want to auto calculate the bus bit timing parameters.
 *                                Recommanded if SYSTEM_FREQUENCY != 80MHz and/or BUS_SPEED != 500KBPS.
 * 
 * Output:
 *      none
 ******************************************************************************/
static void __can_set_speed(CAN_MODULE id, CAN_BUS_SPEED bus_speed, bool set_auto_bit_timing)
{
    if (!set_auto_bit_timing)
    {
        // This configuration has been established for a SYSTEM_FREQUENCY = 80MHz and BUS_SPEED = 500KBPS.    
        p_can_registers_array[id]->CANCFG.SEG2PHTS = 1;             // Phase seg 2 is freely programmable 
        p_can_registers_array[id]->CANCFG.SEG2PH = CAN_BIT_3QT;
        p_can_registers_array[id]->CANCFG.SEG1PH = CAN_BIT_3QT;
        p_can_registers_array[id]->CANCFG.PRSEG = CAN_BIT_3QT;
        p_can_registers_array[id]->CANCFG.SJW = CAN_BIT_2QT;        
        p_can_registers_array[id]->CANCFG.BRP = (PERIPHERAL_FREQ / (bus_speed * ((p_can_registers_array[id]->CANCFG.SEG2PH + 1) + (p_can_registers_array[id]->CANCFG.SEG1PH + 1) + (p_can_registers_array[id]->CANCFG.PRSEG + 1) + 1) * 2)) - 1;      
        p_can_registers_array[id]->CANCFG.SAM = (p_can_registers_array[id]->CANCFG.BRP >= 2) ? 1 : 0;    
    }
    else
    {
        uint8_t N;
        uint8_t BRP;
        uint8_t PRSEG;
        uint8_t SEG1PH;
        uint8_t SEG2PH;

        if (bus_speed == CAN_SPEED_125KBPS)
        {
            PRSEG = 1;  // 1Tq
        }
        else if (bus_speed == CAN_SPEED_250KBPS)
        {
            PRSEG = 2;  // 2Tq
        }
        else if (bus_speed == CAN_SPEED_500KBPS)
        {
            PRSEG = 3;  // 3Tq
        }
        else
        {
            PRSEG = 7;  // 7Tq
        }

        for (N = 8 ; N <= 25 ; N++)
        {
            if ((PERIPHERAL_FREQ % (2 * bus_speed * N)) == 0)
            {
                BRP = (PERIPHERAL_FREQ / (2 * bus_speed * N)) - 1;
                break;
            }
        }
        SEG2PH = N - (N * 3 / 4);   // Sample Point around 75%
        SEG1PH = N - 1 - PRSEG - SEG2PH;

        p_can_registers_array[id]->CANCFG.SEG2PHTS = 1;             // Phase seg 2 is freely programmable 
        p_can_registers_array[id]->CANCFG.SEG2PH = SEG2PH - 1;
        p_can_registers_array[id]->CANCFG.SEG1PH = SEG1PH - 1;
        p_can_registers_array[id]->CANCFG.PRSEG = PRSEG - 1;
        p_can_registers_array[id]->CANCFG.SJW = (p_can_registers_array[id]->CANCFG.SEG2PH >= CAN_BIT_2QT) ? CAN_BIT_2QT : (SEG2PH - 1);
        p_can_registers_array[id]->CANCFG.BRP = BRP;
        p_can_registers_array[id]->CANCFG.SAM = (BRP >= 2) ? 1 : 0; 
    }
    
//    LOG("Bus speed: %dKBPS / BRP: %d / N: %d / SAM: %d / SJW: %dTq / PRSEG: %dTq / SEG1PH: %dTq / SEG2PH: %dTq", 
//            bus_speed, 
//            p_can_registers_array[id]->CANCFG.BRP,
//            (1+(p_can_registers_array[id]->CANCFG.PRSEG+1)+(p_can_registers_array[id]->CANCFG.SEG1PH+1)+(p_can_registers_array[id]->CANCFG.SEG2PH+1)),
//            p_can_registers_array[id]->CANCFG.SAM,
//            (p_can_registers_array[id]->CANCFG.SJW+1),
//            (p_can_registers_array[id]->CANCFG.PRSEG+1),
//            (p_can_registers_array[id]->CANCFG.SEG1PH+1),
//            (p_can_registers_array[id]->CANCFG.SEG2PH+1));
}

/*******************************************************************************
 * Function:
 *      static void __can_configure_fifo_channel(CAN_MODULE id, CAN_CHANNEL channel_id, uint8_t channel_size, bool is_tx_channel, CAN_CHANNEL_EVENT channel_event)
 * 
 * Overview:
 *      This routine is used to configure a FIFO channel. There are up to 32 FIFO channels available.
 *      In this driver, we are using 2 FIFO channels of 32 messages deep each. Channel 0 is used for the Tx frames
 *      and channel 1 is used for Rx frames. 
 * 
 * Input:
 *      id              - The CAN module.
 *      channel_id      - The CAN channel to configure (0..31) (see CAN_CHANNEL).
 *      channel_size    - The message deep (1..32).
 *      is_tx_channel   - The type of message associated with the channel (either TRANSMIT or RECEIVE) (see CAN_FIFOCON_REG).
 *      channel_event   - The type of event(s) associated to the channel. (see CAN_CHANNEL_EVENT). 
 *                        More detail on "can_interrupt_handler" below. We check the flag of the Rx channel.
 * 
 * Output:
 *      none
 ******************************************************************************/
static void __can_configure_fifo_channel(CAN_MODULE id, CAN_CHANNEL channel_id, uint8_t channel_size, bool is_tx_channel, CAN_CHANNEL_EVENT channel_event)
{
    p_can_registers_array[id]->can_fifo_regs[channel_id].CANFIFOCON.FSIZE = ((channel_size - 1) > 31) ? 31 : (channel_size - 1);
    p_can_registers_array[id]->can_fifo_regs[channel_id].CANFIFOINTSET = ((uint32_t) channel_event << 16);
    if (is_tx_channel == CAN_FIFOCON_FIFO_IS_TRANSMIT)
    {
        p_can_registers_array[id]->can_fifo_regs[channel_id].CANFIFOCON.TXEN = CAN_FIFOCON_FIFO_IS_TRANSMIT;                // FIFO channel configure as TX
        p_can_registers_array[id]->can_fifo_regs[channel_id].CANFIFOCON.RTREN = CAN_FIFOCON_TX_RTR_DISABLE;                 // Disable Auto Remote Transmit (RTR) - No automatic TXREQ
        p_can_registers_array[id]->can_fifo_regs[channel_id].CANFIFOCON.TXPR = CAN_FIFOCON_TX_PRIORITY_HIGH_INTERMEDIATE;   // TX Priority is High Intermediate
    }
    else
    {
        p_can_registers_array[id]->can_fifo_regs[channel_id].CANFIFOCON.TXEN = CAN_FIFOCON_FIFO_IS_RECEIVE;                 // FIFO channel configure as RX
        p_can_registers_array[id]->can_fifo_regs[channel_id].CANFIFOCON.DONLY = CAN_FIFOCON_RX_FULL_MESSAGE;                // Full message is stored
    }
}

/*******************************************************************************
 * Function:
 *      static void __can_set_module_event(CAN_MODULE id, CAN_MODULE_EVENT module_event)
 * 
 * Overview:
 *      This routine is used to set the type of event(s) wishes for the CAN module.
 *      If CAN_IRQ is enable then this is the module_event which defines the type of
 *      interruption.
 * 
 * Input:
 *      id              - The CAN module.
 *      module_event    - The type of event(s) wishes for the CAN module (see CAN_MODULE_EVENT).
 * 
 * Output:
 *      none
 ******************************************************************************/
static void __can_set_module_event(CAN_MODULE id, CAN_MODULE_EVENT module_event)
{
    p_can_registers_array[id]->CANINT.v32 = ((uint32_t) module_event << 16);
}

/*******************************************************************************
 * Function:
 *      static void __can_init(CAN_MODULE id, CAN_BUS_SPEED bus_speed, bool set_auto_bit_timing)
 * 
 * Overview:
 *      This routine is used to initialize the CAN module. 
 *      It configures:
 *          + The CAN IRQ and priorities.
 *          + The CAN bit timing.
 *          + The RAM allocation for the FIFO channels (one CAN module used 2 x 32 x 16 bytes). The CAN module uses device RAM for storing CAN messages that need to be transmitted or received.
 *          + The fifo channels (CHANNEL_0 for transmission - 32 messages deep / CHANNEL_1 for reception - 32 messages deep).
 *          + The type of event(s) for the CAN module (we want interruptions on Rx events only).
 * 
 * Input:
 *      id                  - The CAN module to initialize.
 *      bus_speed           - The CAN bus speed (see CAN_BUS_SPEED enumeration).
 *      set_auto_bit_timing - This flag is used to enable the driver to calculate
 *                          the best CAN bit timing parameters in function of the 
 *                          SYSTEM_FREQUENCY and BUS_SPEED.
 * 
 * Output:
 *      none
 ******************************************************************************/
static void __can_init(CAN_MODULE id, CAN_BUS_SPEED bus_speed, bool set_auto_bit_timing)
{
    irq_init(IRQ_CAN1 + id, IRQ_ENABLED, irq_can_priority(id));
    
    p_can_registers_array[id]->CANCON.PERIPHERAL_ENABLE = ENABLE;
    
    __can_set_op_mode(id, CAN_OP_MODE_CONFIGURATION);
    
    __can_set_speed(id, bus_speed, set_auto_bit_timing);     
    
    p_can_registers_array[id]->CANFIFOBA = _VirtToPhys(p_can_params[id]->p_fifo);
    
    __can_configure_fifo_channel(id, CAN_CHANNEL0, 32, CAN_FIFOCON_FIFO_IS_TRANSMIT, 0); // FIFO channel0 for TX (32 messages deep)
    __can_configure_fifo_channel(id, CAN_CHANNEL1, 32, CAN_FIFOCON_FIFO_IS_RECEIVE, CAN_CHANNEL_EVENT_RX_NOT_EMPTY);  // FIFO channel1 for RX (32 messages deep)
    
    __can_set_module_event(id, CAN_MODULE_EVENT_RX);
    
    __can_set_op_mode(id, CAN_OP_MODE_NORMAL);
}

/*******************************************************************************
 * Function:
 *      void can_tasks(can_params_t *var)
 * 
 * Overview:
 *      This routine should be placed in the main while loop and should be executed
 *      as often as possible. Firstly, it configures the CAN module and then manage 
 *      all TX frames. Rx frames are automatically manage in the interrupt handler
 *      (only Rx frames which are been define). 
 *      Filters are used for Rx frames. Thus it limits the call of interrupt handler
 *      if there are a lot of frames on the CAN bus. 
 * 
 * Input:
 *      var         - The can_params_t pointer (this is the can bus variable created
 *                  in CAN_DEF(...)).
 * 
 * Output:
 *      none
 ******************************************************************************/
void can_tasks(can_params_t *var)
{
    if (!var->is_init_done)
    {
        CAN_FILTER filter = CAN_FILTER0;
        uint8_t j;
        
        p_can_params[var->id] = var;

        __can_init(var->id, var->bus_speed, var->set_auto_bit_timing);
        
        if (var->chip_enable._port > 0)
        {
            ports_reset_pin_output(var->chip_enable);
            ports_clr_bit(var->chip_enable);
        }
        
        __can_set_op_mode(var->id, CAN_OP_MODE_CONFIGURATION);
        
        p_can_registers_array[var->id]->can_filter_mask_regs[CAN_MASK0].CANRXM.SID = 0x7ff;
        p_can_registers_array[var->id]->can_filter_mask_regs[CAN_MASK0].CANRXM.MIDE = 0;
        p_can_registers_array[var->id]->can_filter_mask_regs[CAN_MASK0].CANRXM.EID = 0x3ffff;
        
        for (j = 0 ; j < var->number_of_frames ; j++)
        {
            can_frame_params_t *p_frame = (can_frame_params_t *) var->p_frames[j];
            
            if (p_frame->read_write_type == CAN_READ_FRAME)
            {   
                p_can_registers_array[var->id]->can_rx_filter_regs[filter].CANRXF.SID = p_frame->frame.msg_sid.SID;
                p_can_registers_array[var->id]->can_rx_filter_regs[filter].CANRXF.EID = p_frame->frame.msg_eid.EID;
                p_can_registers_array[var->id]->can_rx_filter_regs[filter].CANRXF.EXID = p_frame->frame.msg_eid.IDE;

                p_can_registers_array[var->id]->can_filter_control_regs[filter / 4].CANFLTCON[filter % 4] = (ENABLE << 7) | (CAN_MASK0 << 5) | (CAN_CHANNEL1 << 0);

                filter++;
            }
        }
        
        __can_set_op_mode(var->id, CAN_OP_MODE_NORMAL);
        
        mUpdateTick(var->tick);
        var->is_init_done = true;
    }
    else
    {        
        uint8_t i;
        
        for (i = 0 ; i < var->number_of_frames ; i++)
        {
            can_frame_params_t *p_frame = (can_frame_params_t *) var->p_frames[i];            
            if ((p_frame->read_write_type == CAN_WRITE_FRAME) && ((p_frame->force_transfer) || ((mTickCompare(p_frame->tick) >= p_frame->period) && (p_frame->period > 0))))
            {
                mUpdateTick(p_frame->tick);                
                p_frame->force_transfer = false;                
                can_message_buffer_t * free_transmit_message = (can_message_buffer_t *) _PhysToVirtK1(p_can_registers_array[var->id]->can_fifo_regs[CAN_CHANNEL0].CANFIFOUA);
                memcpy(free_transmit_message, &p_frame->frame, sizeof(can_message_buffer_t));                        
                p_can_registers_array[var->id]->can_fifo_regs[CAN_CHANNEL0].CANFIFOCONSET = 0x00002000; // UINC
                p_can_registers_array[var->id]->can_fifo_regs[CAN_CHANNEL0].CANFIFOCONSET = 0x00000008; // TXREQ                
            }
        }
        
    }
}

/*******************************************************************************
 * Function:
 *      void can_interrupt_handler(CAN_MODULE id)
 * 
 * Overview:
 *      This routine is called when an interruption occur. All data (16 bytes)
 *      is received and transferred from RAM (fifo_ram_allocation) to variable's user.
 *      The frame has a status flag "is_receive_updated" to indicate a new reception. 
 * 
 * Input:
 *      id          - The CAN module which generates the interruption.
 * 
 * Output:
 *      none
 ******************************************************************************/
void can_interrupt_handler(CAN_MODULE id)
{
    if (p_can_registers_array[id]->can_fifo_regs[CAN_CHANNEL1].CANFIFOINT.RXNEMPTYIF)
    {
        uint8_t i;
        
        can_message_buffer_t * free_receive_message = (can_message_buffer_t *) _PhysToVirtK1(p_can_registers_array[id]->can_fifo_regs[CAN_CHANNEL1].CANFIFOUA);

        for (i = 0 ; i < p_can_params[id]->number_of_frames ; i++)
        {
            can_frame_params_t *p_frame = (can_frame_params_t *) p_can_params[id]->p_frames[i];                
            if (p_frame->read_write_type == CAN_READ_FRAME)
            {
                if (    (p_frame->frame.msg_sid.SID == free_receive_message->msg_sid.SID) &&
                        (p_frame->frame.msg_eid.EID == free_receive_message->msg_eid.EID) &&
                        (p_frame->frame.msg_eid.IDE == free_receive_message->msg_eid.IDE))
                    {
                        memcpy(&p_frame->frame, free_receive_message, sizeof(can_message_buffer_t));
                        p_frame->is_receive_updated = true;
                        break;
                    }
            }
        }       
        p_can_registers_array[id]->can_fifo_regs[CAN_CHANNEL1].CANFIFOCONSET = 0x00002000; // UINC        
    }
}
