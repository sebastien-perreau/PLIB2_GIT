/*********************************************************************
 * 
 *	External Grove Motor Driver (TB6612FNG)
 * 
 *	Author : Sébastien PERREAU
 * 
 *  Link: https://wiki.seeedstudio.com/Grove-I2C_Motor_Driver-TB6612FNG/
 * 
 *  IMPORTANT:
 *  The slave_address can be ROM reprogrammed (range 0x01 .. 0x7f). 
 *  It means that the device keep in its memory the new device_address
 *  event after a POWER OFF. The default device_address is 0x14.
 *  A "wait time" of 100 milliseconds must be respected after sending
 *  a "set_address" frame. 
 * 
 *  RECOMMANDATIONS:
 *  If the default device_address is not suitable for you (or if you have more than
 *  1 Grove Motor Driver on your I2C bus) then:
 *      1.  Write a simple program to change the address by a new one thanks 
 *          to the set_address function. The __program_errors function will be called
 *          when set_address frame has been sent in order to show you that you have
 *          to "change" your code. DO NOT FORGET TO WRITE THE NEW ADDRESS ON THE PCB 
 *          OTHERWISE IT WILL BE FORGOTTEN. 
 *      2.  Write your normal code by using the new device_address in the
 *          definition of the grove_motor variable.
 * 
*********************************************************************/

#include "../PLIB2.h"

#warning "e_grove_motor_tb6612fng.c - I2C Frequency can be 100 KHz / 400 KHz"

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
 *      uint8_t e_grove_motor_tb6612fng_deamon(grove_motor_t *var)
 * 
 * Overview:
 *      This routine is the main function for managing the Grove Motor driver. It
 *      should be placed in the 'main while loop' before or after the bus_management
 *      routine.
 * 
 * Input:
 *      *var    - The grove_motor_t pointer variable.
 * 
 * Output:
 *      The value returned represents the state of the i2c_master_state_machine.
 *      See I2C_STATE_MACHIN enumerations in the i2c driver header file.
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
        ret = i2c_master_state_machine(&var->i2c_params, &var->i2c_functions);
        
        if ((ret == _STOP) && (var->i2c_params.data_access.address_register_device == GROVE_MOTOR_CMD_SET_ADDRESS))
        {
            // See IMPORTANT and RECOMMANDATIONS in this heading's file.
            ERROR(__ERROR_GROVE_MOTOR_NEW_DEVICE_ADDRESS);
        }
    }
    
    return ret;
}
