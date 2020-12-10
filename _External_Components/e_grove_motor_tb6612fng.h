#ifndef __DEF_E_GROVE_MOTOR
#define	__DEF_E_GROVE_MOTOR

typedef enum
{
    GROVE_MOTOR_FLAG_STANDBY                            = 0,
    GROVE_MOTOR_FLAG_NOT_STANDBY,
    GROVE_MOTOR_FLAG_SET_ADDRESS,
    GROVE_MOTOR_FLAG_STEPPER_STOP,
    GROVE_MOTOR_FLAG_STEPPER_RUN,
    GROVE_MOTOR_FLAG_STEPPER_KEEP_RUN,
            
    GROVE_MOTOR_FLAG_NUMBERS,
    GROVE_MOTOR_FLAG_NO_FUNCTION                        = 0xff
} GROVE_MOTOR_FLAGS;

typedef enum
{
    GROVE_MOTOR_CMD_BRAKE                               = 0x00,     // Stop the DC motor immediately (channel A or Channel B)
    GROVE_MOTOR_CMD_STOP                                = 0x01,     // Stop the DC motor slowly (channel A or Channel B)
    GROVE_MOTOR_CMD_CLOCKWISE                           = 0x02,     // Start the DC motor in clockwise (channel A or channel B)
    GROVE_MOTOR_CMD_COUNTER_CLOCKWISE                   = 0x03,     // Start the DC motor in counter-clockwise (channel A or channel B)
    GROVE_MOTOR_CMD_STANDBY                             = 0x04,     // Enter standby mode (normal mode)
    GROVE_MOTOR_CMD_NOT_STANDBY                         = 0x05,     // Exit standby mode. Motor driver doesn't do any action in this mode
    GROVE_MOTOR_CMD_STEPPER_RUN                         = 0x06,     // Drive a stepper
    GROVE_MOTOR_CMD_STEPPER_STOP                        = 0x07,     // Stop a stepper
    GROVE_MOTOR_CMD_STEPPER_KEEP_RUN                    = 0x08,     // Keep a stepper running
    GROVE_MOTOR_CMD_SET_ADDRESS                         = 0x11,     // Set a new I2C address
} GROVE_MOTOR_CMDS;

typedef enum
{
    GROVE_MOTOR_FULL_STEP                               = 0,
    GROVE_MOTOR_WAVE_DRIVE,
    GROVE_MOTOR_HALF_STEP,
    GROVE_MOTOR_MICRO_STEPPING
} GROVE_MOTOR_MODE;

typedef struct
{
    // Write only registers
    uint8_t                 dummy_zero;
    uint8_t                 chip_address;
    uint8_t                 stepper_run[6];
    uint8_t                 stepper_keep_run[4];
} grove_motor_regs_t;

typedef struct
{
    bool                    is_init_done;
    I2C_PARAMS              i2c_params;
    I2C_FUNCTIONS           i2c_functions;
    grove_motor_regs_t      registers;
} grove_motor_t;

#define GROVE_MOTOR_INSTANCE(_name, _i2c_module)                                            \
{                                                                                           \
    .is_init_done = false,                                                                  \
    .i2c_params = I2C_PARAMS_INSTANCE(_i2c_module, 0x14, false, (uint8_t*) &_name.registers, TICK_50MS, 0), \
    .i2c_functions =                                                                        \
    {                                                                                       \
        .flags = 0,                                                                         \
        .active_function = 0xff,                                                            \
        .maximum_functions = GROVE_MOTOR_FLAG_NUMBERS,                                      \
        .functions_tab =                                                                    \
        {                                                                                   \
            I2C_DEVICE_ADDRESS_W(_name, GROVE_MOTOR_CMD_STANDBY, dummy_zero, 1*sizeof(uint8_t)),                    \
            I2C_DEVICE_ADDRESS_W(_name, GROVE_MOTOR_CMD_NOT_STANDBY, dummy_zero, 1*sizeof(uint8_t)),                \
            I2C_DEVICE_ADDRESS_W(_name, GROVE_MOTOR_CMD_SET_ADDRESS, chip_address, 1*sizeof(uint8_t)),              \
            I2C_DEVICE_ADDRESS_W(_name, GROVE_MOTOR_CMD_STEPPER_STOP, dummy_zero, 1*sizeof(uint8_t)),               \
            I2C_DEVICE_ADDRESS_W(_name, GROVE_MOTOR_CMD_STEPPER_RUN, stepper_run, 6*sizeof(uint8_t)),               \
            I2C_DEVICE_ADDRESS_W(_name, GROVE_MOTOR_CMD_STEPPER_KEEP_RUN, stepper_keep_run, 4*sizeof(uint8_t))      \
        }                                                                                   \
    },                                                                                      \
    .registers =                                                                            \
    {                                                                                       \
        .dummy_zero = 0,                                                                    \
        .chip_address = 0x14,                                                               \
        .stepper_run = {0},                                                                 \
        .stepper_keep_run = {0}                                                             \
    }                                                                                       \
}

#define GROVE_MOTOR_DEF(_name, _i2c_module)                                                 \
static grove_motor_t _name = GROVE_MOTOR_INSTANCE(_name, _i2c_module)

uint8_t e_grove_motor_tb6612fng_deamon(grove_motor_t *var);

extern __inline__ void __attribute__((always_inline)) e_grove_motor_standby(grove_motor_t *var)
{    
    SET_BIT(var->i2c_functions.flags, GROVE_MOTOR_FLAG_STANDBY);
}

extern __inline__ void __attribute__((always_inline)) e_grove_motor_not_standby(grove_motor_t *var)
{    
    SET_BIT(var->i2c_functions.flags, GROVE_MOTOR_FLAG_NOT_STANDBY);
}

extern __inline__ void __attribute__((always_inline)) e_grove_motor_stepper_stop(grove_motor_t *var)
{    
    SET_BIT(var->i2c_functions.flags, GROVE_MOTOR_FLAG_STEPPER_STOP);
}

extern __inline__ void __attribute__((always_inline)) e_grove_motor_stepper_run(grove_motor_t *var, GROVE_MOTOR_MODE mode, uint8_t rpm, int16_t steps)
{
    uint16_t ms_per_step = (uint16_t) (3000.0 / (float) rpm);
    
    if (steps == -32768) 
    {
        steps = 32767;
    } 
    else if (steps < 0)
    {
        steps = -steps;
    }
    
    var->registers.stepper_run[0] = mode;
    var->registers.stepper_run[1] = ((steps > 0) ? 1 : 0);
    var->registers.stepper_run[2] = (steps >> 0);
    var->registers.stepper_run[3] = (steps >> 8);
    var->registers.stepper_run[4] = (ms_per_step >> 0);
    var->registers.stepper_run[5] = (ms_per_step >> 8);
    
    SET_BIT(var->i2c_functions.flags, GROVE_MOTOR_FLAG_STEPPER_RUN);
}

extern __inline__ void __attribute__((always_inline)) e_grove_motor_stepper_keep_run(grove_motor_t *var, GROVE_MOTOR_MODE mode, uint8_t rpm, bool is_clockwise)
{
    uint16_t ms_per_step = (uint16_t) (3000.0 / (float) rpm);
    
    var->registers.stepper_keep_run[0] = mode;
    var->registers.stepper_keep_run[1] = (is_clockwise ? 5 : 4);
    var->registers.stepper_keep_run[2] = (ms_per_step >> 0);
    var->registers.stepper_keep_run[3] = (ms_per_step >> 8);
    
    SET_BIT(var->i2c_functions.flags, GROVE_MOTOR_FLAG_STEPPER_KEEP_RUN);
}

#endif
