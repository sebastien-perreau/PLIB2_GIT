/********************************************************************
 * 
 *	Section 23 - SPI modules (1, 2, 3 and 4)
 * 
 *	Author : Sebastien PERREAU
 * 
********************************************************************/

#include "../PLIB2.h"

static spi_registers_t * p_spi_registers_array[] =
{
    (spi_registers_t *) &SPI1CON,
    (spi_registers_t *) &SPI2CON,
    (spi_registers_t *) &SPI3CON,
    (spi_registers_t *) &SPI4CON
};
static spi_event_handler_t spi_event_handler[SPI_NUMBER_OF_MODULES] = {NULL};

const uint8_t spi_tx_irq[] = 
{
    _SPI1_TX_IRQ,
    _SPI2_TX_IRQ,
    _SPI3_TX_IRQ,
    _SPI4_TX_IRQ
};

const uint8_t spi_rx_irq[] = 
{
    _SPI1_RX_IRQ,
    _SPI2_RX_IRQ,
    _SPI3_RX_IRQ,
    _SPI4_RX_IRQ
};

const void *p_spi_tx_reg[] = 
{
    (void*) &SPI1BUF,
    (void*) &SPI2BUF,
    (void*) &SPI3BUF,
    (void*) &SPI4BUF
};

const void *p_spi_rx_reg[] = 
{
    (void*) &SPI1BUF,
    (void*) &SPI2BUF,
    (void*) &SPI3BUF,
    (void*) &SPI4BUF
};

static void spi_io_init(SPI_MODULE id, SPI_CONFIG config)
{
    spi_io_t _spi_io[] =
    {
        SPI_IO_INSTANCE(SPI1_CLK, SPI1_SDO, SPI1_SDI, SPI1_SS),
        SPI_IO_INSTANCE(SPI2_CLK, SPI2_SDO, SPI2_SDI, SPI2_SS),
        SPI_IO_INSTANCE(SPI3_CLK, SPI3_SDO, SPI3_SDI, SPI3_SS),
        SPI_IO_INSTANCE(SPI4_CLK, SPI4_SDO, SPI4_SDI, SPI4_SS),
    };
    (!config&~SPI_CONF_MSTEN) ? ports_reset_pin_output(_spi_io[id].SCK) : ports_reset_pin_input(_spi_io[id].SCK);
    ports_reset_pin_output(_spi_io[id].SDO);
    ports_reset_pin_input(_spi_io[id].SDI);
    (!config&~SPI_CONF_SSEN) ? ports_reset_pin_input(_spi_io[id].SS) : 0;
}

static bool spi_is_rx_available(SPI_MODULE id)
{
    if(p_spi_registers_array[id]->SPICON.ENHBUF)
    {
        return p_spi_registers_array[id]->SPISTAT.SPIRBE == 0;
    }
    else
    {
        return p_spi_registers_array[id]->SPISTAT.SPIRBF != 0;
    }
}

static bool spi_is_tx_available(SPI_MODULE id)
{
    if(p_spi_registers_array[id]->SPICON.ENHBUF)
    {
        return p_spi_registers_array[id]->SPISTAT.SPITBF == 0;
    }
    else
    {
        return p_spi_registers_array[id]->SPISTAT.SPITBE != 0;
    }
}

void spi_init(SPI_MODULE id, spi_event_handler_t evt_handler, IRQ_EVENT_TYPE event_type_enable, uint32_t freq_hz, SPI_CONFIG config)
{
    uint32_t dummy;

    spi_event_handler[id] = evt_handler;
    irq_init(IRQ_SPI1E + id, ((evt_handler != NULL) && ((event_type_enable & IRQ_SPI_FAULT) > 0)) ? IRQ_ENABLED : IRQ_DISABLED, irq_spi_priority(id));
    irq_init(IRQ_SPI1RX + id, ((evt_handler != NULL) && ((event_type_enable & IRQ_SPI_RX) > 0)) ? IRQ_ENABLED : IRQ_DISABLED, irq_spi_priority(id));
    irq_init(IRQ_SPI1TX + id, ((evt_handler != NULL) && ((event_type_enable & IRQ_SPI_TX) > 0)) ? IRQ_ENABLED : IRQ_DISABLED, irq_spi_priority(id));
 
    spi_io_init(id, config);
    
    p_spi_registers_array[id]->SPICON.value = 0;
    // Clear the receive buffer
    dummy = p_spi_registers_array[id]->SPIBUF;
    // Clear the overflow
    p_spi_registers_array[id]->SPISTATCLR = _SPI1STAT_SPIROV_MASK;
    spi_set_frequency(id, freq_hz);    
    p_spi_registers_array[id]->SPICON.value = config;
    spi_enable(id, ON);
}

void spi_enable(SPI_MODULE id, bool enable)
{   
    p_spi_registers_array[id]->SPICON.PERIPHERAL_ENABLE = enable;
}

void spi_set_mode(SPI_MODULE id, SPI_CONFIG mode)
{
    p_spi_registers_array[id]->SPICON.MODE16 = ((mode >> 10) & 0x00000001);
    p_spi_registers_array[id]->SPICON.MODE32 = ((mode >> 11) & 0x00000001);
}

void spi_set_frequency(SPI_MODULE id, uint32_t freq_hz)
{
    p_spi_registers_array[id]->SPIBRG = ((uint32_t) (PERIPHERAL_FREQ / freq_hz) >> 1) - 1;
}

bool spi_write_and_read_8(SPI_MODULE id, uint32_t data_w, uint8_t * data_r)
{
    if(spi_is_tx_available(id))
    {
        p_spi_registers_array[id]->SPIBUF = data_w;
        while(!spi_is_rx_available(id));
        *data_r = (uint8_t) p_spi_registers_array[id]->SPIBUF;
        return 0;
    }
    return 1;
}

bool spi_write_and_read_16(SPI_MODULE id, uint32_t data_w, uint16_t * data_r)
{
    if(spi_is_tx_available(id))
    {
        p_spi_registers_array[id]->SPIBUF = data_w;
        while(!spi_is_rx_available(id));
        *data_r = (uint16_t) p_spi_registers_array[id]->SPIBUF;
        return 0;
    }
    return 1;
}

bool spi_write_and_read_32(SPI_MODULE id, uint32_t data_w, uint32_t * data_r)
{
    if(spi_is_tx_available(id))
    {
        p_spi_registers_array[id]->SPIBUF = data_w;
        while(!spi_is_rx_available(id));
        *data_r = (uint32_t) p_spi_registers_array[id]->SPIBUF;
        return 0;
    }
    return 1;
}

/*******************************************************************************
 * Function: 
 *      const uint8_t spi_get_tx_irq(SPI_MODULE id)
 * 
 * Description:
 *      This routine is used to get the TX IRQ number of a SPI module.
 * 
 * Parameters:
 *      id      - The SPI module you want to use.
 * 
 * Return:
 *      The constant TX IRQ number.
 ******************************************************************************/
const uint8_t spi_get_tx_irq(SPI_MODULE id)
{
    return spi_tx_irq[id];
}

/*******************************************************************************
 * Function: 
 *      const uint8_t spi_get_rx_irq(SPI_MODULE id)
 * 
 * Description:
 *      This routine is used to get the RX IRQ number of a SPI module.
 * 
 * Parameters:
 *      id      - The SPI module you want to use.
 * 
 * Return:
 *      The constant RX IRQ number.
 ******************************************************************************/
const uint8_t spi_get_rx_irq(SPI_MODULE id)
{
    return spi_rx_irq[id];
}

/*******************************************************************************
 * Function: 
 *      const void *spi_get_tx_reg(SPI_MODULE id)
 * 
 * Description:
 *      This routine is used to get the TX Register of a SPI module.
 * 
 * Parameters:
 *      id      - The SPI module you want to use.
 * 
 * Return:
 *      The constant pointer of SPI TX REGISTER.
 ******************************************************************************/
const void *spi_get_tx_reg(SPI_MODULE id)
{
    return (void*) p_spi_tx_reg[id];
}

/*******************************************************************************
 * Function: 
 *      const void *spi_get_rx_reg(SPI_MODULE id)
 * 
 * Description:
 *      This routine is used to get the RX Register of a SPI module.
 * 
 * Parameters:
 *      id      - The SPI module you want to use.
 * 
 * Return:
 *      The constant pointer of SPI RX REGISTER.
 ******************************************************************************/
const void *spi_get_rx_reg(SPI_MODULE id)
{
    return (void*) p_spi_rx_reg[id];
}

/*******************************************************************************
 * Function: 
 *      void spi_interrupt_handler(SPI_MODULE id, IRQ_EVENT_TYPE evt_type, uint32_t data)
 * 
 * Description:
 *      This routine is called when an interruption occured. This interrupt 
 *      handler calls the user _event_handler (if existing) otherwise do nothing.
 * 
 * Parameters:
 *      id          - The SPI module you want to use.
 *      evt_type    - The type of event (RX, TX, FAULT...). See IRQ_EVENT_TYPE.
 *      data        - The data (in case of a reception) read in the interruption.
 * 
 * Return:
 *      none
 ******************************************************************************/
void spi_interrupt_handler(SPI_MODULE id, IRQ_EVENT_TYPE evt_type, uint32_t data)
{
    if (spi_event_handler[id] != NULL)
    {
        (*spi_event_handler[id])(id, evt_type, data);
    }
}
