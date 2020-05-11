#ifndef __DEF_SYSTEM
#define	__DEF_SYSTEM

#define FLASH_SPEED_HZ          30000000    //Max Flash speed
#define PB_BUS_MAX_FREQ_HZ      80000000    //Max Peripheral bus speed

#define system_unlock(interrupt_status, dma_status)     \
do                                                      \
{                                                       \
    interrupt_status = irq_disable_interrupts();        \
    dma_status = dma_suspend();                         \
    SYSKEY = 0x00000000;                                \
    SYSKEY = 0xaa996655;                                \
    SYSKEY = 0x556699aa;                                \
}                                                       \
while (0)

#define system_lock(interrupt_status, dma_status)       \
do                                                      \
{                                                       \
    SYSKEY = 0x33333333;                                \
    dma_resume(dma_status);                             \
    irq_restore_interrupts(interrupt_status);           \
}                                                       \
while (0)

uint32_t system_config_performance(uint32_t sys_clock_hz);

#endif