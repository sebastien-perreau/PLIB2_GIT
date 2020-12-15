#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PLIB.X.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PLIB.X.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../_Experimental/_EXAMPLES_.c ../_Experimental/_LOG.c ../_Experimental/pink_lady.c ../_Experimental/sd_card.c ../_External_Components/e_mcp23s17.c ../_External_Components/e_25lc512.c ../_External_Components/e_at42qt2120.c ../_External_Components/e_pca9685.c ../_External_Components/e_veml7700.c ../_External_Components/e_tps92662.c ../_External_Components/e_grove_motor_tb6612fng.c ../_High_Level_Driver/ble.c ../_High_Level_Driver/utilities.c ../_High_Level_Driver/string_advance.c ../_High_Level_Driver/lin.c ../_High_Level_Driver/software_pwm.c ../_Low_Level_Driver/s14_timers.c ../_Low_Level_Driver/s23_spi.c ../_Low_Level_Driver/s17_adc.c ../_Low_Level_Driver/s16_output_compare.c ../_Low_Level_Driver/s24_i2c.c ../_Low_Level_Driver/s12_ports.c ../_Low_Level_Driver/s21_uart.c ../_Low_Level_Driver/s31_dma.c ../_Low_Level_Driver/s07_resets.c ../_Low_Level_Driver/s08_interrupts.c ../_Low_Level_Driver/s00_system.c ../_High_Level_Driver/crc_16.c ../_High_Level_Driver/errors.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o ${OBJECTDIR}/_ext/1717005096/_LOG.o ${OBJECTDIR}/_ext/1717005096/pink_lady.o ${OBJECTDIR}/_ext/1717005096/sd_card.o ${OBJECTDIR}/_ext/830869050/e_mcp23s17.o ${OBJECTDIR}/_ext/830869050/e_25lc512.o ${OBJECTDIR}/_ext/830869050/e_at42qt2120.o ${OBJECTDIR}/_ext/830869050/e_pca9685.o ${OBJECTDIR}/_ext/830869050/e_veml7700.o ${OBJECTDIR}/_ext/830869050/e_tps92662.o ${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o ${OBJECTDIR}/_ext/1180237584/ble.o ${OBJECTDIR}/_ext/1180237584/utilities.o ${OBJECTDIR}/_ext/1180237584/string_advance.o ${OBJECTDIR}/_ext/1180237584/lin.o ${OBJECTDIR}/_ext/1180237584/software_pwm.o ${OBJECTDIR}/_ext/376376446/s14_timers.o ${OBJECTDIR}/_ext/376376446/s23_spi.o ${OBJECTDIR}/_ext/376376446/s17_adc.o ${OBJECTDIR}/_ext/376376446/s16_output_compare.o ${OBJECTDIR}/_ext/376376446/s24_i2c.o ${OBJECTDIR}/_ext/376376446/s12_ports.o ${OBJECTDIR}/_ext/376376446/s21_uart.o ${OBJECTDIR}/_ext/376376446/s31_dma.o ${OBJECTDIR}/_ext/376376446/s07_resets.o ${OBJECTDIR}/_ext/376376446/s08_interrupts.o ${OBJECTDIR}/_ext/376376446/s00_system.o ${OBJECTDIR}/_ext/1180237584/crc_16.o ${OBJECTDIR}/_ext/1180237584/errors.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o.d ${OBJECTDIR}/_ext/1717005096/_LOG.o.d ${OBJECTDIR}/_ext/1717005096/pink_lady.o.d ${OBJECTDIR}/_ext/1717005096/sd_card.o.d ${OBJECTDIR}/_ext/830869050/e_mcp23s17.o.d ${OBJECTDIR}/_ext/830869050/e_25lc512.o.d ${OBJECTDIR}/_ext/830869050/e_at42qt2120.o.d ${OBJECTDIR}/_ext/830869050/e_pca9685.o.d ${OBJECTDIR}/_ext/830869050/e_veml7700.o.d ${OBJECTDIR}/_ext/830869050/e_tps92662.o.d ${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o.d ${OBJECTDIR}/_ext/1180237584/ble.o.d ${OBJECTDIR}/_ext/1180237584/utilities.o.d ${OBJECTDIR}/_ext/1180237584/string_advance.o.d ${OBJECTDIR}/_ext/1180237584/lin.o.d ${OBJECTDIR}/_ext/1180237584/software_pwm.o.d ${OBJECTDIR}/_ext/376376446/s14_timers.o.d ${OBJECTDIR}/_ext/376376446/s23_spi.o.d ${OBJECTDIR}/_ext/376376446/s17_adc.o.d ${OBJECTDIR}/_ext/376376446/s16_output_compare.o.d ${OBJECTDIR}/_ext/376376446/s24_i2c.o.d ${OBJECTDIR}/_ext/376376446/s12_ports.o.d ${OBJECTDIR}/_ext/376376446/s21_uart.o.d ${OBJECTDIR}/_ext/376376446/s31_dma.o.d ${OBJECTDIR}/_ext/376376446/s07_resets.o.d ${OBJECTDIR}/_ext/376376446/s08_interrupts.o.d ${OBJECTDIR}/_ext/376376446/s00_system.o.d ${OBJECTDIR}/_ext/1180237584/crc_16.o.d ${OBJECTDIR}/_ext/1180237584/errors.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o ${OBJECTDIR}/_ext/1717005096/_LOG.o ${OBJECTDIR}/_ext/1717005096/pink_lady.o ${OBJECTDIR}/_ext/1717005096/sd_card.o ${OBJECTDIR}/_ext/830869050/e_mcp23s17.o ${OBJECTDIR}/_ext/830869050/e_25lc512.o ${OBJECTDIR}/_ext/830869050/e_at42qt2120.o ${OBJECTDIR}/_ext/830869050/e_pca9685.o ${OBJECTDIR}/_ext/830869050/e_veml7700.o ${OBJECTDIR}/_ext/830869050/e_tps92662.o ${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o ${OBJECTDIR}/_ext/1180237584/ble.o ${OBJECTDIR}/_ext/1180237584/utilities.o ${OBJECTDIR}/_ext/1180237584/string_advance.o ${OBJECTDIR}/_ext/1180237584/lin.o ${OBJECTDIR}/_ext/1180237584/software_pwm.o ${OBJECTDIR}/_ext/376376446/s14_timers.o ${OBJECTDIR}/_ext/376376446/s23_spi.o ${OBJECTDIR}/_ext/376376446/s17_adc.o ${OBJECTDIR}/_ext/376376446/s16_output_compare.o ${OBJECTDIR}/_ext/376376446/s24_i2c.o ${OBJECTDIR}/_ext/376376446/s12_ports.o ${OBJECTDIR}/_ext/376376446/s21_uart.o ${OBJECTDIR}/_ext/376376446/s31_dma.o ${OBJECTDIR}/_ext/376376446/s07_resets.o ${OBJECTDIR}/_ext/376376446/s08_interrupts.o ${OBJECTDIR}/_ext/376376446/s00_system.o ${OBJECTDIR}/_ext/1180237584/crc_16.o ${OBJECTDIR}/_ext/1180237584/errors.o

# Source Files
SOURCEFILES=../_Experimental/_EXAMPLES_.c ../_Experimental/_LOG.c ../_Experimental/pink_lady.c ../_Experimental/sd_card.c ../_External_Components/e_mcp23s17.c ../_External_Components/e_25lc512.c ../_External_Components/e_at42qt2120.c ../_External_Components/e_pca9685.c ../_External_Components/e_veml7700.c ../_External_Components/e_tps92662.c ../_External_Components/e_grove_motor_tb6612fng.c ../_High_Level_Driver/ble.c ../_High_Level_Driver/utilities.c ../_High_Level_Driver/string_advance.c ../_High_Level_Driver/lin.c ../_High_Level_Driver/software_pwm.c ../_Low_Level_Driver/s14_timers.c ../_Low_Level_Driver/s23_spi.c ../_Low_Level_Driver/s17_adc.c ../_Low_Level_Driver/s16_output_compare.c ../_Low_Level_Driver/s24_i2c.c ../_Low_Level_Driver/s12_ports.c ../_Low_Level_Driver/s21_uart.c ../_Low_Level_Driver/s31_dma.c ../_Low_Level_Driver/s07_resets.c ../_Low_Level_Driver/s08_interrupts.c ../_Low_Level_Driver/s00_system.c ../_High_Level_Driver/crc_16.c ../_High_Level_Driver/errors.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/PLIB.X.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o: ../_Experimental/_EXAMPLES_.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717005096" 
	@${RM} ${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o.d" -o ${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o ../_Experimental/_EXAMPLES_.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1717005096/_LOG.o: ../_Experimental/_LOG.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717005096" 
	@${RM} ${OBJECTDIR}/_ext/1717005096/_LOG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717005096/_LOG.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717005096/_LOG.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1717005096/_LOG.o.d" -o ${OBJECTDIR}/_ext/1717005096/_LOG.o ../_Experimental/_LOG.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1717005096/pink_lady.o: ../_Experimental/pink_lady.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717005096" 
	@${RM} ${OBJECTDIR}/_ext/1717005096/pink_lady.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717005096/pink_lady.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717005096/pink_lady.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1717005096/pink_lady.o.d" -o ${OBJECTDIR}/_ext/1717005096/pink_lady.o ../_Experimental/pink_lady.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1717005096/sd_card.o: ../_Experimental/sd_card.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717005096" 
	@${RM} ${OBJECTDIR}/_ext/1717005096/sd_card.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717005096/sd_card.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717005096/sd_card.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1717005096/sd_card.o.d" -o ${OBJECTDIR}/_ext/1717005096/sd_card.o ../_Experimental/sd_card.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/830869050/e_mcp23s17.o: ../_External_Components/e_mcp23s17.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/830869050" 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_mcp23s17.o.d 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_mcp23s17.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/830869050/e_mcp23s17.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/830869050/e_mcp23s17.o.d" -o ${OBJECTDIR}/_ext/830869050/e_mcp23s17.o ../_External_Components/e_mcp23s17.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/830869050/e_25lc512.o: ../_External_Components/e_25lc512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/830869050" 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_25lc512.o.d 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_25lc512.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/830869050/e_25lc512.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/830869050/e_25lc512.o.d" -o ${OBJECTDIR}/_ext/830869050/e_25lc512.o ../_External_Components/e_25lc512.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/830869050/e_at42qt2120.o: ../_External_Components/e_at42qt2120.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/830869050" 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_at42qt2120.o.d 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_at42qt2120.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/830869050/e_at42qt2120.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/830869050/e_at42qt2120.o.d" -o ${OBJECTDIR}/_ext/830869050/e_at42qt2120.o ../_External_Components/e_at42qt2120.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/830869050/e_pca9685.o: ../_External_Components/e_pca9685.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/830869050" 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_pca9685.o.d 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_pca9685.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/830869050/e_pca9685.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/830869050/e_pca9685.o.d" -o ${OBJECTDIR}/_ext/830869050/e_pca9685.o ../_External_Components/e_pca9685.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/830869050/e_veml7700.o: ../_External_Components/e_veml7700.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/830869050" 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_veml7700.o.d 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_veml7700.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/830869050/e_veml7700.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/830869050/e_veml7700.o.d" -o ${OBJECTDIR}/_ext/830869050/e_veml7700.o ../_External_Components/e_veml7700.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/830869050/e_tps92662.o: ../_External_Components/e_tps92662.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/830869050" 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_tps92662.o.d 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_tps92662.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/830869050/e_tps92662.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/830869050/e_tps92662.o.d" -o ${OBJECTDIR}/_ext/830869050/e_tps92662.o ../_External_Components/e_tps92662.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o: ../_External_Components/e_grove_motor_tb6612fng.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/830869050" 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o.d 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o.d" -o ${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o ../_External_Components/e_grove_motor_tb6612fng.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1180237584/ble.o: ../_High_Level_Driver/ble.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1180237584" 
	@${RM} ${OBJECTDIR}/_ext/1180237584/ble.o.d 
	@${RM} ${OBJECTDIR}/_ext/1180237584/ble.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1180237584/ble.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1180237584/ble.o.d" -o ${OBJECTDIR}/_ext/1180237584/ble.o ../_High_Level_Driver/ble.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1180237584/utilities.o: ../_High_Level_Driver/utilities.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1180237584" 
	@${RM} ${OBJECTDIR}/_ext/1180237584/utilities.o.d 
	@${RM} ${OBJECTDIR}/_ext/1180237584/utilities.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1180237584/utilities.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1180237584/utilities.o.d" -o ${OBJECTDIR}/_ext/1180237584/utilities.o ../_High_Level_Driver/utilities.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1180237584/string_advance.o: ../_High_Level_Driver/string_advance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1180237584" 
	@${RM} ${OBJECTDIR}/_ext/1180237584/string_advance.o.d 
	@${RM} ${OBJECTDIR}/_ext/1180237584/string_advance.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1180237584/string_advance.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1180237584/string_advance.o.d" -o ${OBJECTDIR}/_ext/1180237584/string_advance.o ../_High_Level_Driver/string_advance.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1180237584/lin.o: ../_High_Level_Driver/lin.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1180237584" 
	@${RM} ${OBJECTDIR}/_ext/1180237584/lin.o.d 
	@${RM} ${OBJECTDIR}/_ext/1180237584/lin.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1180237584/lin.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1180237584/lin.o.d" -o ${OBJECTDIR}/_ext/1180237584/lin.o ../_High_Level_Driver/lin.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1180237584/software_pwm.o: ../_High_Level_Driver/software_pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1180237584" 
	@${RM} ${OBJECTDIR}/_ext/1180237584/software_pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1180237584/software_pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1180237584/software_pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1180237584/software_pwm.o.d" -o ${OBJECTDIR}/_ext/1180237584/software_pwm.o ../_High_Level_Driver/software_pwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s14_timers.o: ../_Low_Level_Driver/s14_timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s14_timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s14_timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s14_timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s14_timers.o.d" -o ${OBJECTDIR}/_ext/376376446/s14_timers.o ../_Low_Level_Driver/s14_timers.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s23_spi.o: ../_Low_Level_Driver/s23_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s23_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s23_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s23_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s23_spi.o.d" -o ${OBJECTDIR}/_ext/376376446/s23_spi.o ../_Low_Level_Driver/s23_spi.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s17_adc.o: ../_Low_Level_Driver/s17_adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s17_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s17_adc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s17_adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s17_adc.o.d" -o ${OBJECTDIR}/_ext/376376446/s17_adc.o ../_Low_Level_Driver/s17_adc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s16_output_compare.o: ../_Low_Level_Driver/s16_output_compare.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s16_output_compare.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s16_output_compare.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s16_output_compare.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s16_output_compare.o.d" -o ${OBJECTDIR}/_ext/376376446/s16_output_compare.o ../_Low_Level_Driver/s16_output_compare.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s24_i2c.o: ../_Low_Level_Driver/s24_i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s24_i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s24_i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s24_i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s24_i2c.o.d" -o ${OBJECTDIR}/_ext/376376446/s24_i2c.o ../_Low_Level_Driver/s24_i2c.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s12_ports.o: ../_Low_Level_Driver/s12_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s12_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s12_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s12_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s12_ports.o.d" -o ${OBJECTDIR}/_ext/376376446/s12_ports.o ../_Low_Level_Driver/s12_ports.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s21_uart.o: ../_Low_Level_Driver/s21_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s21_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s21_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s21_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s21_uart.o.d" -o ${OBJECTDIR}/_ext/376376446/s21_uart.o ../_Low_Level_Driver/s21_uart.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s31_dma.o: ../_Low_Level_Driver/s31_dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s31_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s31_dma.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s31_dma.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s31_dma.o.d" -o ${OBJECTDIR}/_ext/376376446/s31_dma.o ../_Low_Level_Driver/s31_dma.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s07_resets.o: ../_Low_Level_Driver/s07_resets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s07_resets.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s07_resets.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s07_resets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s07_resets.o.d" -o ${OBJECTDIR}/_ext/376376446/s07_resets.o ../_Low_Level_Driver/s07_resets.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s08_interrupts.o: ../_Low_Level_Driver/s08_interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s08_interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s08_interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s08_interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s08_interrupts.o.d" -o ${OBJECTDIR}/_ext/376376446/s08_interrupts.o ../_Low_Level_Driver/s08_interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s00_system.o: ../_Low_Level_Driver/s00_system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s00_system.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s00_system.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s00_system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s00_system.o.d" -o ${OBJECTDIR}/_ext/376376446/s00_system.o ../_Low_Level_Driver/s00_system.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1180237584/crc_16.o: ../_High_Level_Driver/crc_16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1180237584" 
	@${RM} ${OBJECTDIR}/_ext/1180237584/crc_16.o.d 
	@${RM} ${OBJECTDIR}/_ext/1180237584/crc_16.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1180237584/crc_16.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1180237584/crc_16.o.d" -o ${OBJECTDIR}/_ext/1180237584/crc_16.o ../_High_Level_Driver/crc_16.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1180237584/errors.o: ../_High_Level_Driver/errors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1180237584" 
	@${RM} ${OBJECTDIR}/_ext/1180237584/errors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1180237584/errors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1180237584/errors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1180237584/errors.o.d" -o ${OBJECTDIR}/_ext/1180237584/errors.o ../_High_Level_Driver/errors.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
else
${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o: ../_Experimental/_EXAMPLES_.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717005096" 
	@${RM} ${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o.d" -o ${OBJECTDIR}/_ext/1717005096/_EXAMPLES_.o ../_Experimental/_EXAMPLES_.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1717005096/_LOG.o: ../_Experimental/_LOG.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717005096" 
	@${RM} ${OBJECTDIR}/_ext/1717005096/_LOG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717005096/_LOG.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717005096/_LOG.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1717005096/_LOG.o.d" -o ${OBJECTDIR}/_ext/1717005096/_LOG.o ../_Experimental/_LOG.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1717005096/pink_lady.o: ../_Experimental/pink_lady.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717005096" 
	@${RM} ${OBJECTDIR}/_ext/1717005096/pink_lady.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717005096/pink_lady.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717005096/pink_lady.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1717005096/pink_lady.o.d" -o ${OBJECTDIR}/_ext/1717005096/pink_lady.o ../_Experimental/pink_lady.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1717005096/sd_card.o: ../_Experimental/sd_card.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1717005096" 
	@${RM} ${OBJECTDIR}/_ext/1717005096/sd_card.o.d 
	@${RM} ${OBJECTDIR}/_ext/1717005096/sd_card.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1717005096/sd_card.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1717005096/sd_card.o.d" -o ${OBJECTDIR}/_ext/1717005096/sd_card.o ../_Experimental/sd_card.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/830869050/e_mcp23s17.o: ../_External_Components/e_mcp23s17.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/830869050" 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_mcp23s17.o.d 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_mcp23s17.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/830869050/e_mcp23s17.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/830869050/e_mcp23s17.o.d" -o ${OBJECTDIR}/_ext/830869050/e_mcp23s17.o ../_External_Components/e_mcp23s17.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/830869050/e_25lc512.o: ../_External_Components/e_25lc512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/830869050" 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_25lc512.o.d 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_25lc512.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/830869050/e_25lc512.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/830869050/e_25lc512.o.d" -o ${OBJECTDIR}/_ext/830869050/e_25lc512.o ../_External_Components/e_25lc512.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/830869050/e_at42qt2120.o: ../_External_Components/e_at42qt2120.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/830869050" 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_at42qt2120.o.d 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_at42qt2120.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/830869050/e_at42qt2120.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/830869050/e_at42qt2120.o.d" -o ${OBJECTDIR}/_ext/830869050/e_at42qt2120.o ../_External_Components/e_at42qt2120.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/830869050/e_pca9685.o: ../_External_Components/e_pca9685.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/830869050" 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_pca9685.o.d 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_pca9685.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/830869050/e_pca9685.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/830869050/e_pca9685.o.d" -o ${OBJECTDIR}/_ext/830869050/e_pca9685.o ../_External_Components/e_pca9685.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/830869050/e_veml7700.o: ../_External_Components/e_veml7700.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/830869050" 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_veml7700.o.d 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_veml7700.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/830869050/e_veml7700.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/830869050/e_veml7700.o.d" -o ${OBJECTDIR}/_ext/830869050/e_veml7700.o ../_External_Components/e_veml7700.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/830869050/e_tps92662.o: ../_External_Components/e_tps92662.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/830869050" 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_tps92662.o.d 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_tps92662.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/830869050/e_tps92662.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/830869050/e_tps92662.o.d" -o ${OBJECTDIR}/_ext/830869050/e_tps92662.o ../_External_Components/e_tps92662.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o: ../_External_Components/e_grove_motor_tb6612fng.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/830869050" 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o.d 
	@${RM} ${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o.d" -o ${OBJECTDIR}/_ext/830869050/e_grove_motor_tb6612fng.o ../_External_Components/e_grove_motor_tb6612fng.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1180237584/ble.o: ../_High_Level_Driver/ble.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1180237584" 
	@${RM} ${OBJECTDIR}/_ext/1180237584/ble.o.d 
	@${RM} ${OBJECTDIR}/_ext/1180237584/ble.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1180237584/ble.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1180237584/ble.o.d" -o ${OBJECTDIR}/_ext/1180237584/ble.o ../_High_Level_Driver/ble.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1180237584/utilities.o: ../_High_Level_Driver/utilities.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1180237584" 
	@${RM} ${OBJECTDIR}/_ext/1180237584/utilities.o.d 
	@${RM} ${OBJECTDIR}/_ext/1180237584/utilities.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1180237584/utilities.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1180237584/utilities.o.d" -o ${OBJECTDIR}/_ext/1180237584/utilities.o ../_High_Level_Driver/utilities.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1180237584/string_advance.o: ../_High_Level_Driver/string_advance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1180237584" 
	@${RM} ${OBJECTDIR}/_ext/1180237584/string_advance.o.d 
	@${RM} ${OBJECTDIR}/_ext/1180237584/string_advance.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1180237584/string_advance.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1180237584/string_advance.o.d" -o ${OBJECTDIR}/_ext/1180237584/string_advance.o ../_High_Level_Driver/string_advance.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1180237584/lin.o: ../_High_Level_Driver/lin.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1180237584" 
	@${RM} ${OBJECTDIR}/_ext/1180237584/lin.o.d 
	@${RM} ${OBJECTDIR}/_ext/1180237584/lin.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1180237584/lin.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1180237584/lin.o.d" -o ${OBJECTDIR}/_ext/1180237584/lin.o ../_High_Level_Driver/lin.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1180237584/software_pwm.o: ../_High_Level_Driver/software_pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1180237584" 
	@${RM} ${OBJECTDIR}/_ext/1180237584/software_pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1180237584/software_pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1180237584/software_pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1180237584/software_pwm.o.d" -o ${OBJECTDIR}/_ext/1180237584/software_pwm.o ../_High_Level_Driver/software_pwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s14_timers.o: ../_Low_Level_Driver/s14_timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s14_timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s14_timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s14_timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s14_timers.o.d" -o ${OBJECTDIR}/_ext/376376446/s14_timers.o ../_Low_Level_Driver/s14_timers.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s23_spi.o: ../_Low_Level_Driver/s23_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s23_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s23_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s23_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s23_spi.o.d" -o ${OBJECTDIR}/_ext/376376446/s23_spi.o ../_Low_Level_Driver/s23_spi.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s17_adc.o: ../_Low_Level_Driver/s17_adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s17_adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s17_adc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s17_adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s17_adc.o.d" -o ${OBJECTDIR}/_ext/376376446/s17_adc.o ../_Low_Level_Driver/s17_adc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s16_output_compare.o: ../_Low_Level_Driver/s16_output_compare.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s16_output_compare.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s16_output_compare.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s16_output_compare.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s16_output_compare.o.d" -o ${OBJECTDIR}/_ext/376376446/s16_output_compare.o ../_Low_Level_Driver/s16_output_compare.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s24_i2c.o: ../_Low_Level_Driver/s24_i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s24_i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s24_i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s24_i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s24_i2c.o.d" -o ${OBJECTDIR}/_ext/376376446/s24_i2c.o ../_Low_Level_Driver/s24_i2c.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s12_ports.o: ../_Low_Level_Driver/s12_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s12_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s12_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s12_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s12_ports.o.d" -o ${OBJECTDIR}/_ext/376376446/s12_ports.o ../_Low_Level_Driver/s12_ports.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s21_uart.o: ../_Low_Level_Driver/s21_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s21_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s21_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s21_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s21_uart.o.d" -o ${OBJECTDIR}/_ext/376376446/s21_uart.o ../_Low_Level_Driver/s21_uart.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s31_dma.o: ../_Low_Level_Driver/s31_dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s31_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s31_dma.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s31_dma.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s31_dma.o.d" -o ${OBJECTDIR}/_ext/376376446/s31_dma.o ../_Low_Level_Driver/s31_dma.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s07_resets.o: ../_Low_Level_Driver/s07_resets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s07_resets.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s07_resets.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s07_resets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s07_resets.o.d" -o ${OBJECTDIR}/_ext/376376446/s07_resets.o ../_Low_Level_Driver/s07_resets.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s08_interrupts.o: ../_Low_Level_Driver/s08_interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s08_interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s08_interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s08_interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s08_interrupts.o.d" -o ${OBJECTDIR}/_ext/376376446/s08_interrupts.o ../_Low_Level_Driver/s08_interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/376376446/s00_system.o: ../_Low_Level_Driver/s00_system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/376376446" 
	@${RM} ${OBJECTDIR}/_ext/376376446/s00_system.o.d 
	@${RM} ${OBJECTDIR}/_ext/376376446/s00_system.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/376376446/s00_system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/376376446/s00_system.o.d" -o ${OBJECTDIR}/_ext/376376446/s00_system.o ../_Low_Level_Driver/s00_system.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1180237584/crc_16.o: ../_High_Level_Driver/crc_16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1180237584" 
	@${RM} ${OBJECTDIR}/_ext/1180237584/crc_16.o.d 
	@${RM} ${OBJECTDIR}/_ext/1180237584/crc_16.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1180237584/crc_16.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1180237584/crc_16.o.d" -o ${OBJECTDIR}/_ext/1180237584/crc_16.o ../_High_Level_Driver/crc_16.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1180237584/errors.o: ../_High_Level_Driver/errors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1180237584" 
	@${RM} ${OBJECTDIR}/_ext/1180237584/errors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1180237584/errors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1180237584/errors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O3 -MMD -MF "${OBJECTDIR}/_ext/1180237584/errors.o.d" -o ${OBJECTDIR}/_ext/1180237584/errors.o ../_High_Level_Driver/errors.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: archive
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PLIB.X.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_AR} $(MP_EXTRA_AR_PRE)  r dist/${CND_CONF}/${IMAGE_TYPE}/PLIB.X.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    
else
dist/${CND_CONF}/${IMAGE_TYPE}/PLIB.X.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_AR} $(MP_EXTRA_AR_PRE)  r dist/${CND_CONF}/${IMAGE_TYPE}/PLIB.X.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
