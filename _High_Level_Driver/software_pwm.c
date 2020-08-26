/*********************************************************************
 *  Software PWM driver
 *  Author : Sébastien PERREAU
 * 
 *  Revision history    :
 *              12/03/2019              - Initial release
 *
 *  Timings (200 hertz with resolution = 1):
 *  ---------------------------------------
 *  busy = occupation time in the interrupt routine periodically (200 hertz
 *  with a resolution of 1:1 => 200 x 255 = 51000 hertz = 1 interruption
 *  each 19,607 micro-seconds).
 *  4 S-PWM : 8,38 % busy of 19,607 us. 
 *  7 S-PWM : 13,59 % busy of 19,607 us.
 *  14 S-PWM : 22,48 % busy of 19,607 us.
 *  20 S-PWM : 30,14 % busy of 19,607 us.
 *  30 S-PWM : 42,92 % busy of 19,607 us.
 ********************************************************************/

#include "../PLIB2.h"

static SOFTWAPRE_PWM_PARAMS  * p_software_pwm = NULL;
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

/*******************************************************************************
  Function:
    static void software_pwm_event_handler(uint8_t id)

  Description:
    This static routine is the event handler for the software PWM. Periodically,
    this handler is called to update the output pins. The interruption provides
    by a TIMER module, so it is a TIMER module which generates this event handler.

  Parameters:
    id      - The TIMER module which generates the event handler. 
  *****************************************************************************/
static void software_pwm_event_handler(uint8_t id)
{    
    static uint8_t i;
    
    UNUSED_PARAMETER(id);
    
    for (i = 0 ; i < p_software_pwm->number_of_pwm_used ; i++)
    {
        
        if (p_software_pwm->pwm[i] == 255)
        {
            p_ports_registers_array[p_software_pwm->io[i]._port - 1]->LATSET = (uint32_t) (1 << p_software_pwm->io[i]._indice);
        }
        else if (p_software_pwm->pwm[i] > p_software_pwm->counter)
        {
            p_ports_registers_array[p_software_pwm->io[i]._port - 1]->LATSET = (uint32_t) (1 << p_software_pwm->io[i]._indice);
        }
        else
        {
            p_ports_registers_array[p_software_pwm->io[i]._port - 1]->LATCLR = (uint32_t) (1 << p_software_pwm->io[i]._indice);
        }
    }    
    
    p_software_pwm->counter += p_software_pwm->resolution;
}

/*******************************************************************************
  Function:
    void software_pwm_init(SOFTWAPRE_PWM_PARAMS *var)

  Description:
    This routine is used to initialize the software PWM driver.

  Parameters:
    var*    - A pointer of SOFTWAPRE_PWM_PARAMS.
  *****************************************************************************/
void software_pwm_init(SOFTWAPRE_PWM_PARAMS *var)
{
    static uint8_t i;
    
    p_software_pwm = var;
    
    for (i = 0 ; i < var->number_of_pwm_used ; i++)
    {
        ports_reset_pin_output(var->io[i]);
    }
    
    timer_init_2345_hz(var->timer_module, software_pwm_event_handler, TMR_ON | TMR_SOURCE_INT | TMR_IDLE_CON | TMR_GATE_OFF, var->frequency_hz * 255 / var->resolution);
}
