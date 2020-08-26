/********************************************************************* 
 * 
 *	Section 12 - PORTS module 
 * 
 *	Author : Sébastien PERREAU
 *
 ********************************************************************/

#include "../PLIB2.h"

static ports_registers_t * p_ports_registers_array[] =
{
	(ports_registers_t *) &TRISA,
	(ports_registers_t *) &TRISB,
	(ports_registers_t *) &TRISC,
	(ports_registers_t *) &TRISD,
	(ports_registers_t *) &TRISE,
	(ports_registers_t *) &TRISF,
	(ports_registers_t *) &TRISG
};
static ports_event_handler_t ports_event_handler = NULL;

/*******************************************************************************
 * Function:
 *      void ports_change_notice_init(uint32_t cn_pull_up, uint32_t cn_pins_enable, ports_event_handler_t evt_handler)
 *
 * Description:
 *      This routine is used to initialize the change notice feature of the PORT module.
 *      The CN module allow both, detections on a pin and pin pull-up configuration (on
 *      CN pin only).
 *
 * Parameters:
 *      cn_pull_up      - The pull-up configuration (CN0_PULLUP_ENABLE | CN1_PULLUP_ENABLE...).
 *      cn_pins_enable  - The CN pin enable configuration (enable one or more pins to trigger
 *                      a CN event when a detection (low or high) is made). The CN flag is set
 *                      when using this feature.
 *      evt_handler     - The handler (function) to call when an interruption occurs.
 * 
 * Return:
 *      none
 ******************************************************************************/
void ports_change_notice_init(uint32_t cn_pull_up, uint32_t cn_pins_enable, ports_event_handler_t evt_handler)
{
    ports_event_handler = evt_handler;
    irq_init(IRQ_CN, (evt_handler != NULL) ? IRQ_ENABLED : IRQ_DISABLED, irq_change_notice_priority());
    CNCON = ((evt_handler != NULL) && (cn_pins_enable > 0)) ? CN_ON : CN_OFF;
    CNEN = cn_pins_enable;      // CN pins enable
    CNPUE = cn_pull_up;         // CN pins pull-up enable
}

/*******************************************************************************
 * Function:
 *      void ports_reset_all_pins_input()
 *
 * Description:
 *      This routine is used to initialize all PIC32 pins as there default state 
 *      (INPUT mode and PORT state as 0).
 *
 * Parameters:
 *      none
 * 
 * Return:
 *      none
 ******************************************************************************/
void ports_reset_all_pins_input()
{
    uint8_t i;
    for (i = 0 ; i < (sizeof(p_ports_registers_array)/sizeof(ports_registers_t)) ; i++)
    {
        p_ports_registers_array[i]->TRISSET =  0xffffffff;
        p_ports_registers_array[i]->LATCLR = 0xffffffff;
    }
}

/*******************************************************************************
 * Function:
 *      void ports_reset_pin_input(_io_t io)
 *
 * Description:
 *      This routine is used to initialize ONE pin as input 
 *      (tris.pin = input & port.pin = 0).
 *
 * Parameters:
 *      io      - The _io_t parameter (_port & _indice).
 * 
 * Return:
 *      none
 ******************************************************************************/
void ports_reset_pin_input(_io_t io)
{
    p_ports_registers_array[io._port - 1]->TRISSET =  (uint32_t) (1 << io._indice);
    p_ports_registers_array[io._port - 1]->LATCLR = (uint32_t) (1 << io._indice);
}

/*******************************************************************************
 * Function:
 *      void ports_reset_pin_output(_io_t io)
 *
 * Description:
 *      This routine is used to initialize ONE pin as output 
 *      (tris.pin = output & port.pin = 0).
 *
 * Parameters:
 *      io  - The _io_t parameter (_port & _indice).
 * 
 * Return:
 *      none
 ******************************************************************************/
void ports_reset_pin_output(_io_t io)
{
    p_ports_registers_array[io._port - 1]->TRISCLR =  (uint32_t) (1 << io._indice);
    p_ports_registers_array[io._port - 1]->LATCLR = (uint32_t) (1 << io._indice);
}

/*******************************************************************************
 * Function:
 *      bool ports_get_bit(_io_t io)
 *
 * Description:
 *      This routine is used to get a ONE pin's value (1 or 0).
 *
 * Parameters:
 *      io      - The _io_t parameter (_port & _indice).
 *
 * Return:
 *      true if bit as a high level, false if bit as a low level. 
 ******************************************************************************/
bool ports_get_bit(_io_t io)
{
    return ((p_ports_registers_array[io._port - 1]->PORT & (1 << io._indice)) >> io._indice);
}

/*******************************************************************************
 * Function:
 *      void ports_set_bit(_io_t io)
 *
 * Description:
 *      This routine is used to set (1) a ONE pin's bit.
 *
 * Parameters:
 *      io      - The _io_t parameter (_port & _indice).
 * 
 * Return:
 *      none
 ******************************************************************************/
void ports_set_bit(_io_t io)
{
    p_ports_registers_array[io._port - 1]->LATSET = (uint32_t) (1 << io._indice);
}

/*******************************************************************************
 * Function:
 *      void ports_clr_bit(_io_t io)
 *
 * Description:
 *      This routine is used to clear (0) a ONE pin's bit.
 *
 * Parameters:
 *      io      - The _io_t parameter (_port & _indice).
 * 
 * Return:
 *      none
 ******************************************************************************/
void ports_clr_bit(_io_t io)
{
    p_ports_registers_array[io._port - 1]->LATCLR = (uint32_t) (1 << io._indice);
}

/*******************************************************************************
 * Function:
 *      void ports_toggle_bit(_io_t io)
 *
 * Description:
 *      This routine is used to toggle (!pin) a ONE pin's bit.
 *
 * Parameters:
 *      io      - The _io_t parameter (_port & _indice).
 * 
 * Return:
 *      none
 ******************************************************************************/
void ports_toggle_bit(_io_t io)
{
    p_ports_registers_array[io._port - 1]->LATINV = (uint32_t) (1 << io._indice);
}

/*******************************************************************************
 * Function:
 *      void ports_interrupt_handler()
 *
 * Description:
 *      This routine is called when an interruption occurs. This interrupt 
 *      handler calls the user _event_handler (if existing) otherwise do nothing.
 *
 * Parameters:
 *      none
 * 
 * Return:
 *      none
 ******************************************************************************/
void ports_interrupt_handler()
{
    if (ports_event_handler != NULL)
    {
        (*ports_event_handler)();
    }
}
