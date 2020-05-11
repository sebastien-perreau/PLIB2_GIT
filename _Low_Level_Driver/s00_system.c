/*********************************************************************
*	System driver
*	Author : Sébastien PERREAU
*********************************************************************/

#include "../PLIB2.h"

/*******************************************************************************
 * Function:
 *      static void kseg0_cache_off()
 * 
 * Description:
 *      This routine is used to disable cacheability of KSEG0.
 * 
 * Parameters:
 *      none
 * 
 * Return:
 *      none
 ******************************************************************************/
static void kseg0_cache_off()
{
	register unsigned long tmp;
	asm("mfc0 %0,$16,0" :  "=r"(tmp));
	tmp = (tmp & ~7) | 2;
	asm("mtc0 %0,$16,0" :: "r" (tmp));
}

/*******************************************************************************
 * Function:
 *      static void kseg0_cache_on()
 * 
 * Description:
 *      This routine is used to enable cacheability of KSEG0.
 * 
 * Parameters:
 *      none
 * 
 * Return:
 *      none
 ******************************************************************************/
static void kseg0_cache_on()
{
	register unsigned long tmp;
	asm("mfc0 %0,$16,0" :  "=r"(tmp));
	tmp = (tmp & ~7) | 3;
	asm("mtc0 %0,$16,0" :: "r" (tmp));
}

/*******************************************************************************
 * Function:
 *      static void osc_set_pb_div(uint32_t osc_pb_div)
 * 
 * Description:
 *      This routine configures peripheral bus divisor.
 * 
 * Parameters:
 *      osc_pb_div          - Desired PB divider.
 * 
 * Return:
 *      none
 ******************************************************************************/
static void osc_set_pb_div(uint32_t osc_pb_div)
{
	uint32_t dma_status;
	uint32_t interrupt_status;
	__OSCCONbits_t oscBits;

	system_unlock(interrupt_status, dma_status);
	
	oscBits.w = OSCCON;		// read to be in sync. flush any pending write
	oscBits.PBDIV = 0;
	oscBits.w |= osc_pb_div;	
	OSCCON = oscBits.w;		// write back
	oscBits.w = OSCCON;		// make sure the write occurred before returning from this function
	
	system_lock(interrupt_status, dma_status);
}

/*******************************************************************************
 * Function:
 *      static uint32_t system_config_pb(uint32_t sys_clock_hz)
 * 
 * Description:
 *      The function sets the PB divider to the optimum value.
 * 
 *      Note: The interrupts are disabled briefly, the DMA is suspended and the 
 *      system is unlocked while performing the operation. Upon return the previous 
 *      status of the interrupts and the DMA are restored. The system is re-locked.
 * 
 * Parameters:
 *      sys_clock_hz        - System clock frequency in hertz.
 * 
 * Return:
 *      The PB clock frequency in hertz.
 ******************************************************************************/
static uint32_t system_config_pb(uint32_t sys_clock_hz)
{
    uint32_t pb_div;
    uint32_t pb_clock;

    pb_clock = sys_clock_hz;

    if (sys_clock_hz > PB_BUS_MAX_FREQ_HZ)
    {
        pb_div = (1 << _OSCCON_PBDIV_POSITION);
        pb_clock >>= 1;
    }
    else
    {
        pb_div = (0 << _OSCCON_PBDIV_POSITION);
    }

    osc_set_pb_div(pb_div);

    return pb_clock;
}

/*******************************************************************************
 * Function:
 *      static uint32_t system_config_wait_states_and_pb(uint32_t sys_clock_hz)
 * 
 * Description:
 *      The function sets the PB divider and the Flash Wait states to the optimum value.
 * 
 *      Note: The interrupts are disabled briefly, the DMA is suspended and the 
 *      system is unlocked while performing the operation. Upon return the previous 
 *      status of the interrupts and the DMA are restored. The system is re-locked.
 * 
 * Parameters:
 *      sys_clock_hz        - System clock frequency in hertz.
 * 
 * Return:
 *      The PB clock frequency in hertz.
 ******************************************************************************/
static uint32_t system_config_wait_states_and_pb(uint32_t sys_clock_hz)
{
    uint32_t wait_states = 0;
    uint32_t pb_clock;
    uint32_t interrupt_status;

    pb_clock = system_config_pb(sys_clock_hz);

    while (sys_clock_hz > FLASH_SPEED_HZ)
    {
        wait_states++;
        sys_clock_hz -= FLASH_SPEED_HZ;
    }

    interrupt_status = irq_disable_interrupts();
    CHECON = wait_states;
    irq_restore_interrupts(interrupt_status);    

    return pb_clock;
}

/*******************************************************************************
 * Function:
 *      uint32_t system_config_performance(uint32_t sys_clock_hz)
 * 
 * Description:
 *      The function sets the PB divider, the Flash Wait states and the DRM wait 
 *      states to the optimum value. It also enables the cacheability for the K0 segment.
 * 
 * Parameters:
 *      sys_clock_hz        - System clock frequency in hertz.
 * 
 * Return:
 *      The PB clock frequency in hertz.
 ******************************************************************************/
uint32_t system_config_performance(uint32_t sys_clock_hz)
{
    uint32_t pb_clk;
    uint32_t cache_status;
    uint32_t interrupt_status;

    pb_clk = system_config_wait_states_and_pb(sys_clock_hz);
    interrupt_status = irq_disable_interrupts();   
    
    BMXCONCLR = _BMXCON_BMXWSDRM_MASK;    

    cache_status = CHECON;
    cache_status |= (3 << _CHECON_PREFEN_POSITION);
    CHECON = cache_status;
    kseg0_cache_on();

    irq_restore_interrupts(interrupt_status);    

    return pb_clk;
}

