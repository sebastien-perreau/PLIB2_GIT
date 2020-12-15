/*********************************************************************
 * 
 *	Error function
 * 
 *	Author : Sebastien PERREAU
 * 
*********************************************************************/

#include "../PLIB2.h"

/*******************************************************************************
 * Function: 
 *      void __program_errors(__PROGRAM_ERRORS code_error)
 * 
 * Description:
 *      This function is used to indicate that an error occurs. It can be placed
 *      wherever the user want. For example if using a DMA module and no more 
 *      DMA channel are available then this routine is called to indicate the issue. 
 *      The initialization part is necessary for using UART1 (LOG driver) and the
 *      three LEDs of the PIC32 board. 
 *      Once this first part is terminated, the routine enters in an infinite 
 *      loop. THe three LEDs are blinking (to indicate the program is running) and
 *      a LOG is periodically sent with a "code_error". 
 * 
 * Parameters:
 *      code_error:     See __PROGRAM_ERRORS for more details on the type of 
 *                      code error.
 * 
 * Return:
 *      none
 ******************************************************************************/
void __errors(__ERRORS code_error)
{
    state_machine_t sm_errors = {0}; 
    
    mInitIOAsOutput(LED1);
    mInitIOAsOutput(LED2);
    mInitIOAsOutput(LED3);
    
    // Because SPI3, I2C3 and UART1 are sharing the same pins, be sur to DISABLE 
    // SPI3 and I2C3 in order to use UART1 for LOG.
    spi_enable(SPI3, DISABLE);
    i2c_enable(I2C3, DISABLE);
    log_init(UART1, UART_BAUDRATE_2M);
    
    LOG("Error Occurs - Code %d", code_error);
    
    do
    {
        if (mTickCompare(sm_errors.tick) >= TICK_200MS)
        {
            mUpdateTick(sm_errors.tick);
            sm_errors.index++;
        }
        
        switch (sm_errors.index)
        {
            case 0:
                
                mSetIO(LED1);
                mClrIO(LED2);
                mClrIO(LED3);
                break;
                
            case 1:
                
                mClrIO(LED1);
                mSetIO(LED2);
                mClrIO(LED3);
                break;
                
            case 2:
                
                mClrIO(LED1);
                mClrIO(LED2);
                mSetIO(LED3);
                break;
                
            case 3:
                                
                mSetIO(LED1);
                mSetIO(LED2);
                mSetIO(LED3);
                sm_errors.index++;
                break;
                
            case 4:
                
                // Do nothing...
                break;
                
            default:
                
                sm_errors.index = 0;
                break;
        }
    }
    while (1);
}
