/*********************************************************************
 * 
 *	Section 07 - Reset driver
 * 
 *	Author : Sébastien PERREAU
 * 
 ********************************************************************/

#include "../PLIB2.h"

/*******************************************************************************
 * Function:
 *      void software_reset(void)
 * 
 * Overview:
 *      Software device reset. 
 *          The following steps are performed by this function:
 *			Step 1 - Execute "unlock" sequence to access the RSWRST register.
 *			Step 2 - Write a '1' to RSWRST.SWRST bit to arm the software reset.
 *			Step 3 - A Read of the RSWRST register must follow the write.  This
 *				action triggers the software reset, which should occur on the next
 *				clock cycle.
 *      Note: The read instruction must be following with either 4 nop instructions 
 *      (fills the instruction pipe) or a while(1)loop to ensure no instructions can 
 *      access the bus before reset occurs.
 * 
 * Input:
 *      none
 * 
 * Output:
 *      none
 ******************************************************************************/
void software_reset(void)
{    
    uint32_t interrupt_status;
	uint32_t dma_status;
	volatile uint32_t *p = &RSWRST;

	system_unlock(&interrupt_status, &dma_status);
	RSWRSTSET=_RSWRST_SWRST_MASK;
	*p;

	while(1);
}
 