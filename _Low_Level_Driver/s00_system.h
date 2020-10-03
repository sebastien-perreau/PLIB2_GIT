#ifndef __DEF_SYSTEM
#define	__DEF_SYSTEM

#define FLASH_SPEED_HZ          30000000    //Max Flash speed
#define PB_BUS_MAX_FREQ_HZ      80000000    //Max Peripheral bus speed

/*********************************************************************
 * Function:        
 *      unsigned int _VirtToPhys(const void* p)
 *
 * Overview:		
 *      Virtual to physical translation helper.
 *
 * Input:			
 *      p	- pointer to be converted.
 *
 * Output:          
 *      a physical address corresponding to the virtual input pointer
 ********************************************************************/
extern __inline__ unsigned int __attribute__((always_inline)) _VirtToPhys(const void* p)
{
	return (int)p<0?((int)p&0x1fffffffL):(unsigned int)((unsigned char*)p+0x40000000L);
}

/*********************************************************************
 * Function:        
 *      void* _PhysToVirtK0(unsigned int a)
 *
 * Overview:		
 *      Physical to virtual translation helper.
 *
 * Input:			
 *      a	- address to be converted.
 *
 * Output:          
 *      a virtual pointer corresponding to the physical input address
 ********************************************************************/
extern __inline__ void* __attribute__((always_inline)) _PhysToVirtK0(unsigned int a)
{
	return a<0x40000000L?(void*)(a|0x80000000L):(void*)(a-0x40000000L);
}

/*********************************************************************
 * Function:        
 *      void* _PhysToVirtK1(unsigned int a)
 *
 * Overview:		
 *      Physical to virtual translation helper.
 *
 * Input:			
 *      a	- address to be converted.
 *
 * Output:          
 *      a virtual pointer corresponding to the physical input address
 ********************************************************************/
extern __inline__ void* __attribute__((always_inline)) _PhysToVirtK1(unsigned int a)
{
	return a<0x40000000L?(void*)(a|0xa0000000L):(void*)(a-0x40000000L);
}

uint32_t system_config_performance(uint32_t sys_clock_hz);
void system_lock(uint32_t interrupt_status, uint32_t dma_status);
void system_unlock(uint32_t *p_interrupt_status, uint32_t *p_dma_status);

#endif