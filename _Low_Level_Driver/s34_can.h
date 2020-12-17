#ifndef __DEF_CAN
#define	__DEF_CAN

typedef enum
{
    CAN1                        = 0,
    CAN2,
    CAN_NUMBER_OF_MODULES
} CAN_MODULE;

typedef union 
{
    struct 
    {
        unsigned            TBF:1;
        unsigned            RBF:1;
        unsigned            R_W:1;
        unsigned            S:1;
        unsigned            P:1;
        unsigned            D_A:1;
        unsigned            I2COV:1;
        unsigned            IWCOL:1;
        unsigned            ADD10:1;
        unsigned            GCSTAT:1;
        unsigned            BCL:1;
        unsigned            :3;
        unsigned            TRSTAT:1;
        unsigned            ACKSTAT:1;
        unsigned            :16;
    };
    struct 
    {
        uint32_t            value;
    };
} can_stat_reg_t;

typedef struct
{
    volatile i2c_con_reg_t  I2CCON;
	volatile uint32_t       I2CCONCLR;
	volatile uint32_t       I2CCONSET;
	volatile uint32_t       I2CCONINV;
    
    volatile i2c_stat_reg_t I2CSTAT;
	volatile uint32_t       I2CSTATCLR;
	volatile uint32_t       I2CSTATSET;
	volatile uint32_t       I2CSTATINV;
} can_registers_t;

typedef void (*can_event_handler_t)(uint8_t id, IRQ_EVENT_TYPE event_type, uint32_t event_value);

#endif
