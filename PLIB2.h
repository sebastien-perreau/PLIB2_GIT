#ifndef __DEF_INCLUDES_PLIB
#define	__DEF_INCLUDES_PLIB

#include <xc.h>                     // xc pic32 header
#include <sys/attribs.h>

#include <math.h>
#include <string.h>
#include <lega-c/machine/types.h>
#include "ctype.h"
#include <GenericTypeDefs.h>

#include "defines.h"

#include "_Low_Level_Driver/s00_system.h"
#include "_Low_Level_Driver/s08_interrupts.h"
#include "_Low_Level_Driver/s07_resets.h"
#include "_Low_Level_Driver/s12_ports.h"

#include "_High_Level_Driver/utilities.h"
#include "_High_Level_Driver/string_advance.h"

#include "_Low_Level_Driver/s14_timers.h"
#include "_Low_Level_Driver/s16_output_compare.h"
#include "_Low_Level_Driver/s17_adc.h"
#include "_Low_Level_Driver/s21_uart.h"
#include "_Low_Level_Driver/s23_spi.h"
#include "_Low_Level_Driver/s24_i2c.h"
#include "_Low_Level_Driver/s31_dma.h"

#include "_High_Level_Driver/software_pwm.h"
#include "_High_Level_Driver/lin.h"
#include "_High_Level_Driver/ble.h"

#include "_External_Components/e_25lc512.h"
#include "_External_Components/e_mcp23s17.h"
#include "_External_Components/e_at42qt2120.h"
#include "_External_Components/e_pca9685.h"
#include "_External_Components/e_veml7700.h"
#include "_External_Components/e_tps92662.h"
#include "_External_Components/e_grove_motor_tb6612fng.h"

#include "_Experimental/_EXAMPLES_.h"
#include "_Experimental/_LOG.h"
#include "_Experimental/pink_lady.h"
#include "_Experimental/fat_file_system.h"
#include "_Experimental/sd_card.h"

uint8_t _ledStatus;

#endif
