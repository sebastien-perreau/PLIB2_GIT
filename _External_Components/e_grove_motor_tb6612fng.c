/*********************************************************************
 * 
 *	External Grove Motor Driver (TB6612FNG)
 * 
 *	Author : Sébastien PERREAU
 * 
 *  Link: https://wiki.seeedstudio.com/Grove-I2C_Motor_Driver-TB6612FNG/
 * 
*********************************************************************/

#include "../PLIB2.h"

#warning "e_grove_motor_tb6612fng.c - I2C Frequency should be 400 KHz"

/*******************************************************************************
 * Function:
 *      static void e_grove_motor_tb6612fng_handler(uint8_t id, IRQ_EVENT_TYPE evt_type, uint32_t data)
 * 
 * Overview:
 *      This routine is the event handler called by the interrupt routine (only if enable).
 *      To use this event handler, it must be passed as parameter in the i2c_init_as_master
 *      function (initialization sequence). Do not forget to enable the IRQ(s). 
 *      If you do not want to use it then passed NULL as parameter and disable IRQ(s). 
 * 
 * Input:
 *      id          - Identifier of the I2C module which generates the event (ex: I2C1)
 *      evt_type    - Type of event (see. IRQ_EVENT_TYPE for I2C bus)
 *      data        - The data read by the I2C module (data will be always 8-bits size but for 
 *                  compatibility with other serial bus, the variable is a 32-bits type)
 * 
 * Output:
 *      none
 ******************************************************************************/
static void e_grove_motor_tb6612fng_handler(uint8_t id, IRQ_EVENT_TYPE evt_type, uint32_t data)
{
    switch (evt_type)
    {
        case IRQ_I2C_MASTER:
            /*
             * Events: 
             * - Start
             * - Repeated Start
             * - Stop
             * - data transmit + ACK receive (9th clock)
             * _ data receive + ACK transmit (9th clock)
             */
            break;
        case IRQ_I2C_SLAVE:
            break;
        case IRQ_I2C_BUS_COLISION:
            break;
    }
}

/*******************************************************************************
 * Function:
 * 
 * Overview:
 * 
 * Input:
 * 
 * Output:
 ******************************************************************************/
uint8_t e_grove_motor_tb6612fng_deamon(grove_motor_t *var)
{
    uint8_t ret;
    
    if (!var->is_init_done)
    {
        i2c_init_as_master(var->i2c_params.module, NULL, IRQ_NONE, I2C_FREQUENCY_400KHZ, I2C_CONTINUE_ON_IDLE | I2C_DISABLE_SMBUS);
        var->is_init_done = true;
        
        e_grove_motor_standby(var);
        
        ret = _BUS_I2C_INIT;
    }
    else
    {
        if (var->i2c_functions.flags > 0)
        {
            ret = i2c_master_state_machine(&var->i2c_params, &var->i2c_functions);
        }
    }
    
    return ret;
}
