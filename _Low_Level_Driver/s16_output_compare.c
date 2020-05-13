/*********************************************************************
 * 
 *	Section 16 - Output Compare modules (1, 2, 3, 4 and 5)
 * 
 *	Author : Sébastien PERREAU
 *
 ********************************************************************/

#include "../PLIB2.h"

extern const output_compare_registers_t * output_compare_registers[];
const output_compare_registers_t * output_compare_registers[] =
{
    (output_compare_registers_t *)_OCMP1_BASE_ADDRESS,
    (output_compare_registers_t *)_OCMP2_BASE_ADDRESS,
    (output_compare_registers_t *)_OCMP3_BASE_ADDRESS,
    (output_compare_registers_t *)_OCMP4_BASE_ADDRESS,
    (output_compare_registers_t *)_OCMP5_BASE_ADDRESS
};

/*******************************************************************************
 * Function:
 *      void pwm_init(PWM_MODULE_ENABLE pwm_ids, uint32_t t2_freq_hz, uint32_t t3_freq_hz)
 *
 * Description:
 *      This routine is used to initialize a output compare module in PWM mode.
 *      The 2 TIMER modules are automatically set if they are needed by a PWM.
 *      As example, if only TIMER2 is used to manage the PWM(s) then TIMER3 stay
 *      free-to-use.
 *
 * Parameters:
 *      pwm_ids         - The PWM(s) you want to enable (see PWM_MODULE_ENABLE).
 *      t2_freq_hz      - The timer 2 frequency in hertz (if an OC module use it).
 *      t3_freq_hz      - The timer 3 frequency in hertz (if an OC module use it).
 * 
 * Return:
 *      none
 ******************************************************************************/
void pwm_init(PWM_MODULE_ENABLE pwm_ids, uint32_t t2_freq_hz, uint32_t t3_freq_hz)
{
    uint8_t i;
    
    for (i = 0 ; i < PWM_NUMBER_OF_MODULES ; i++)
    {
        output_compare_registers_t * p_oc = (output_compare_registers_t *)output_compare_registers[i];
        p_oc->OCxR = 0X0000;
        p_oc->OCxRS = 0x0000;
        if (((pwm_ids >> (2*i)) & 1) > 0)
        {
            p_oc->OCxCON = (OC_ON | OC_PWM_FAULT_PIN_DISABLE | OC_TIMER2_SRC);
        }
        else if (((pwm_ids >> (2*i)) & 2) > 0)
        {
            p_oc->OCxCON = (OC_ON | OC_PWM_FAULT_PIN_DISABLE | OC_TIMER3_SRC);
        }
    }
    
    if ((pwm_ids & PWM_T2_MASK) > 0)
    {
        timer_init_2345_hz(TIMER2, NULL, TMR_ON | TMR_SOURCE_INT | TMR_IDLE_CON | TMR_GATE_OFF, t2_freq_hz);
    }
    if ((pwm_ids & PWM_T3_MASK) > 0)
    {
        timer_init_2345_hz(TIMER3, NULL, TMR_ON | TMR_SOURCE_INT | TMR_IDLE_CON | TMR_GATE_OFF, t3_freq_hz);
    }
}

/*******************************************************************************
 * Function:
 *      void pwm_set_duty_cycle(PWM_MODULE pwm_id, uint8_t dc)
 *
 * Description:
 *      This routine is used to set a duty cycle on an OC (PWM) channel. The range
 *      is 0 to 255 (0% to 100%).
 *
 * Parameters:
 *      pwm_id      - The OC (PWM) channel you want to use.
 *      dc          - The duty cycle (0..255)
 * 
 * Return:
 *      none
 ******************************************************************************/
void pwm_set_duty_cycle(PWM_MODULE pwm_id, uint8_t dc)
{
    output_compare_registers_t * p_oc = (output_compare_registers_t *)output_compare_registers[pwm_id];
    uint32_t prx = ((p_oc->OCxCON & OC_TIMER3_SRC) > 0) ? PR3 : PR2;
    
    p_oc->OCxRS = (dc * (prx + 1)) / 255;
}
