#ifndef __DEF_CAN
#define	__DEF_CAN

/*
 * The CAN module uses device RAM for storing CAN messages that need to be transmitted or received. 
 * The CAN module by itself does not have user-accessible message buffers.
 * 
 * Up to 32 FIFOs channels, each contains 1 .. 32 Message Buffer. 1 Message buffer can be 8 or 16 bytes length.
 */
#define CAN_SIZE_FIFO_RAM_ALLOCATION (2 * 32 * 16)   // Allocation of 2 FIFOs, each 16 Message Buffer deep of 16 bytes.

typedef enum
{
    CAN1                        = 0,
    CAN2,
    CAN_NUMBER_OF_MODULES
} CAN_MODULE;

typedef enum
{
    CAN_MASK0                   = 0,
    CAN_MASK1,
    CAN_MASK2,
    CAN_MASK3,
    CAN_NUMBER_OF_MASKS
} CAN_MASK;

typedef enum
{
    CAN_FILTER0                 = 0,
    CAN_FILTER1,
    CAN_FILTER2,
    CAN_FILTER3,
    CAN_FILTER4,
    CAN_FILTER5,
    CAN_FILTER6,
    CAN_FILTER7,
    CAN_FILTER8,
    CAN_FILTER9,
    CAN_FILTER10,
    CAN_FILTER11,
    CAN_FILTER12,
    CAN_FILTER13,
    CAN_FILTER14,
    CAN_FILTER15,
    CAN_FILTER16,
    CAN_FILTER17,
    CAN_FILTER18,
    CAN_FILTER19,
    CAN_FILTER20,
    CAN_FILTER21,
    CAN_FILTER22,
    CAN_FILTER23,
    CAN_FILTER24,
    CAN_FILTER25,
    CAN_FILTER26,
    CAN_FILTER27,
    CAN_FILTER28,
    CAN_FILTER29,
    CAN_FILTER30,
    CAN_FILTER31,
    CAN_NUMBER_OF_FILTERS
} CAN_FILTER;

typedef enum
{
    CAN_FILTER_CON0             = 0,
    CAN_FILTER_CON1,
    CAN_FILTER_CON2,
    CAN_FILTER_CON3,
    CAN_FILTER_CON4,
    CAN_FILTER_CON5,
    CAN_FILTER_CON6,
    CAN_FILTER_CON7,
    CAN_NUMBER_OF_FILTER_CONTROLS
} CAN_FILTER_CONTROL;

typedef enum
{
    CAN_CHANNEL0                = 0,
    CAN_CHANNEL1,
    CAN_CHANNEL2,
    CAN_CHANNEL3,
    CAN_CHANNEL4,
    CAN_CHANNEL5,
    CAN_CHANNEL6,
    CAN_CHANNEL7,
    CAN_CHANNEL8,
    CAN_CHANNEL9,
    CAN_CHANNEL10,
    CAN_CHANNEL11,
    CAN_CHANNEL12,
    CAN_CHANNEL13,
    CAN_CHANNEL14,
    CAN_CHANNEL15,
    CAN_CHANNEL16,
    CAN_CHANNEL17,
    CAN_CHANNEL18,
    CAN_CHANNEL19,
    CAN_CHANNEL20,
    CAN_CHANNEL21,
    CAN_CHANNEL22,
    CAN_CHANNEL23,
    CAN_CHANNEL24,
    CAN_CHANNEL25,
    CAN_CHANNEL26,
    CAN_CHANNEL27,
    CAN_CHANNEL28,
    CAN_CHANNEL29,
    CAN_CHANNEL30,
    CAN_CHANNEL31,
    CAN_NUMBER_OF_CHANNELS
} CAN_CHANNEL;

typedef enum
{
    CAN_SPEED_125KBPS                   = 125000,
    CAN_SPEED_250KBPS                   = 250000,
    CAN_SPEED_500KBPS                   = 500000,
    CAN_SPEED_1MBPS                     = 1000000
} CAN_BUS_SPEED;

typedef enum
{
    CAN_BUS_BIT_TIMING_AUTO             = 1,
    CAN_BUS_BIT_TIMING_FIXED            = 0
} CAN_BUS_BIT_TIMING;

typedef enum
{
    CAN_OP_MODE_NORMAL                  = 0,
    CAN_OP_MODE_DISABLE                 = 1,
    CAN_OP_MODE_LOOPBACK                = 2,
    CAN_OP_MODE_LISTEN_ONLY             = 3,
    CAN_OP_MODE_CONFIGURATION           = 4,
    CAN_OP_MODE_LISTEN_ALL_MESSAGES     = 7
} CAN_OP_MODE;

typedef enum
{
    CAN_BIT_1QT                         = 0,
    CAN_BIT_2QT,
    CAN_BIT_3QT,
    CAN_BIT_4QT,
    CAN_BIT_5QT,
    CAN_BIT_6QT,
    CAN_BIT_7QT,
    CAN_BIT_8QT
} CAN_BIT_TIME_QUANTUM;

typedef enum
{
    CAN_FIFOCON_TX_PRIORITY_LOWEST              = 0,
    CAN_FIFOCON_TX_PRIORITY_LOW_INTERMEDIATE    = 1,
    CAN_FIFOCON_TX_PRIORITY_HIGH_INTERMEDIATE   = 2,
    CAN_FIFOCON_TX_PRIORITY_HIGHEST             = 3,
            
    CAN_FIFOCON_TX_RTR_ENABLE                   = 1,
    CAN_FIFOCON_TX_RTR_DISABLE                  = 0,
            
    CAN_FIFOCON_TX_SEND                         = 1,
    CAN_FIFOCON_TX_ABORD                        = 0,
            
    CAN_FIFOCON_RX_DATA_ONLY                    = 1,
    CAN_FIFOCON_RX_FULL_MESSAGE                 = 0,
            
    CAN_FIFOCON_FIFO_IS_TRANSMIT                = 1,
    CAN_FIFOCON_FIFO_IS_RECEIVE                 = 0,
            
} CAN_FIFOCON_REG;

typedef enum 
{
	CAN_MODULE_EVENT_TX                         = 0x0001,       // TX channel event. This event will occur if any of the TX Channel events are active. 
	CAN_MODULE_EVENT_RX                         = 0x0002,       // RX channel event. This event will occur if any of the RX Channel events are active.
	CAN_MODULE_EVENT_TIMESTAMP_TIMER_OVERFLOW   = 0x0004,       // CAN Timer Stamp Timer Overflow event occurs. This event occurs when the Timestamp Timer has overflowed.
	CAN_MODULE_EVENT_OPERATION_MODE_CHANGE      = 0x0008,       // CAN Operation Mode Change Event. This event occurs when the CAN module has changed it's operating mode successfully.
    CAN_MODULE_EVENT_RX_OVERFLOW                = 0x0800,       // CAN RX Channel Overflow Event. This event occurs when any of the RX Channel has overflowed.
	CAN_MODULE_EVENT_SYSTEM_ERROR               = 0x1000,       // CAN System Error Event. This event occurs when CAN module tries to access an invalid Device RAM location.
	CAN_MODULE_EVENT_BUS_ERROR                  = 0x2000,       // CAN Bus Error Event. This event occurs when the CAN module cannot access the system bus.
	CAN_MODULE_EVENT_BUS_ACTIVITY_WAKEUP        = 0x4000,       // CAN Bus Actvity Wakeup. This event occurs when the device is in sleep mode and bus activity is detected on the CAN bus.
	CAN_MODULE_EVENT_INVALID_RX_MESSAGE         = 0x8000        // CAN Bus Invalid RX Message Event. This event occurs when the CAN module receives an Invalid message.
} CAN_MODULE_EVENT;

typedef enum 
{
	CAN_CHANNEL_EVENT_RX_NOT_EMPTY              = 0x0001,       // CAN RX Channel Not Empty Event Mask
	CAN_CHANNEL_EVENT_RX_HALF_FULL              = 0x0002,       // CAN RX Channel Half Full Event Mask
	CAN_CHANNEL_EVENT_RX_FULL                   = 0x0004,       // CAN RX Channel Full Event Mask
	CAN_CHANNEL_EVENT_RX_OVERFLOW               = 0x0008,       // CAN RX Channel Overflow Event Mask
	CAN_CHANNEL_EVENT_RX_ANY_EVENT              = 0x000f,       // CAN RX Channel Any Event Mask
	CAN_CHANNEL_EVENT_TX_EMPTY                  = 0x0100,       // CAN TX Channel Empty Event Mask
	CAN_CHANNEL_EVENT_TX_HALF_EMPTY             = 0x0200,       // CAN TX Channel Half Empty Event Mask
	CAN_CHANNEL_EVENT_TX_NOT_FULL               = 0x0400,       // CAN TX Channel Not Full Event Mask
	CAN_CHANNEL_EVENT_TX_ANY_EVENT              = 0x0700        // CAN TX Channel Any Event Mask
} CAN_CHANNEL_EVENT;
    
typedef union 
{
    struct 
    {
        unsigned                RXNEMPTYIF:1;       // [ R ] - Receive Buffer Not Empty Interrupt Flag bit
        unsigned                RXHALFIF:1;         // [ R ] - Receive FIFO Half Full Interrupt Flag bit
        unsigned                RXFULLIF:1;         // [ R ] - Receive FIFO Full Interrupt Flag bit
        unsigned                RXOVFLIF:1;         // [ R ] - Receive FIFO Overflow Interrupt Flag bit
        unsigned                :4;
        unsigned                TXEMPTYIF:1;        // [ R ] - Transmit FIFO Empty Interrupt Flag bit
        unsigned                TXHALFIF:1;         // [ R ] - FIFO Transmit FIFO Half Empty Interrupt Flag bit
        unsigned                TXNFULLIF:1;        // [ R ] - Transmit FIFO Not Full Interrupt Flag bit
        unsigned                :5;
        
        unsigned                RXNEMPTYIE:1;       // [ R/W ] - Empty Interrupt Enable bit
        unsigned                RXHALFIE:1;         // [ R/W ] - FIFO Half Full Interrupt Enable bit
        unsigned                RXFULLIE:1;         // [ R/W ] - Full Interrupt Enable bit
        unsigned                RXOVFLIE:1;         // [ R/W ] - Overflow Interrupt Enable bit
        unsigned                :4;
        unsigned                TXEMPTYIE:1;        // [ R/W ] - Transmit FIFO Empty Interrupt Enable bit
        unsigned                TXHALFIE:1;         // [ R/W ] - Transmit FIFO Half Full Interrupt Enable bit
        unsigned                TXNFULLIE:1;        // [ R/W ] - Transmit FIFO Not Full Interrupt Enable bit
        unsigned                :5;
    };
    struct 
    {
        uint32_t                v32;
    };
} can_fifoint_reg_t;
    
typedef union 
{
    struct 
    {
        unsigned                TXPR:2;             // [ R/W ] - Message Transmit Priority bits (11 = Highest Message Priority / 10 = High Intermediate Message Priority / 01 = Low Intermediate Message Priority / 00 = Lowest Message Priority)
        unsigned                RTREN:1;            // [ R/W ] - Auto RTR Enable bit (1 = When a remote transmit is received, TXREQ will be set)
        unsigned                TXREQ:1;            // [ R/W ] - Message Send Request (only if "TXEN = 1" - Setting this bit to '1' requests sending a message. The bit will automatically clear when all the messages queued in the FIFO are successfully sent. Clearing the bit to '0' while set ('1') will request a message abort.)
        unsigned                TXERR:1;            // [ R ] - Error Detected During Transmission bit
        unsigned                TXLARB:1;           // [ R ] - Message Lost Arbitration bit (1 = Message lost arbitration while being sent)
        unsigned                TXABAT:1;           // [ R ] - Message Aborted bit
        unsigned                TXEN:1;             // [ R/W ] - TX/RX Buffer Selection bit (1 = FIFO is a Transmit FIFO / 0 = FIFO is a Receive FIFO)
        unsigned                :4;
        unsigned                DONLY:1;            // [ R/W ] -  Store Message Data Only bit (only if "TXEN = 0" - 1 = Only data bytes will be stored in the FIFO / 0 = Full message is stored, including identifier)
        unsigned                UINC:1;             // [ S/HC ] - Increment Head/Tail bit (When this bit is set the FIFO (TXEN ? head : tail) will increment by a single message)
        unsigned                FRESET:1;           // [ S/HC ] - FIFO Reset bits (FIFO will be reset when bit is set, cleared by hardware when FIFO is reset. After setting, the user should poll if this bit is clear before taking any action)
        unsigned                :1;
        unsigned                FSIZE:5;            // [ R/W ] - FIFO Size bits (11111 = FIFO is 32 messages deep / ... / 00001 = FIFO is 2 messages deep / 00000 = FIFO is 1 message deep)
        unsigned                :11;
    };
    struct 
    {
        uint32_t                v32;
    };
} can_fifocon_reg_t;
    
typedef union 
{
    struct 
    {
        unsigned                EID:18;             // [ R/W ] - Extended Identifier bits (1 = Message address bit SIDx must be ?1? to match filter / 0 = Message address bit SIDx must be ?0? to match filter)
        unsigned                :1;
        unsigned                EXID:1;             // [ R/W ] - Extended Identifier Enable bits (1 = Match only messages with extended identifier addresses / 0 = Match only messages with standard identifier addresses)
        unsigned                :1;
        unsigned                SID:11;             // [ R/W ] - Standard Identifier bits (1 = Message address bit EIDx must be ?1? to match filter / 0 = Message address bit EIDx must be ?0? to match filter)
    };
    struct 
    {
        uint32_t                v32;
    };
} can_rxf_reg_t;
    
typedef union 
{
    struct 
    {
        unsigned                EID:18;             // [ R/W ] - Extended Identifier bits (1 = Include bit, EIDx, in filter comparison / 0 = Bit EIDx is ?don?t care? in filter operation)
        unsigned                :1;
        unsigned                MIDE:1;             // [ R/W ] - Identifier Receive Mode bit (1 = Match only message types (standard/extended address) that correspond to the EXID bit in filter / 0 = Match either standard or extended address message if filters match (that is, if (Filter SID) = (Message SID) or if (FILTER SID/EID) = (Message SID/EID)))
        unsigned                :1;
        unsigned                SID:11;             // [ R/W ] - Standard Identifier bits (1 = Include bit, SIDx, in filter comparison / 0 = Bit SIDx is ?don?t care? in filter operation)
    };
    struct 
    {
        uint32_t                v32;
    };
} can_rxm_reg_t;
    
typedef union 
{
    struct 
    {
        unsigned                CANTSPRE:16;        // [ R/W ] - CAN Time Stamp Timer Prescaler bits (65535 = CAN time stamp timer (CANTS) increments every 65,535 system clocks / ... / 0 = CAN time stamp timer (CANTS) increments every system clock)
        unsigned                CANTS:16;           // [ R/W ] - CAN Time Stamp Timer bits (This is a free-running timer that increments every CANTSPRE system clocks when the CANCAP bit (CiCON<20>) is set.)
    };
    struct 
    {
        uint32_t                v32;
    };
} can_tmr_reg_t;
    
typedef union 
{
    struct 
    {
        unsigned                RERRCNT:8;          // [ R ] - Receive Error Counter
        unsigned                TERRCNT:8;          // [ R ] - Transmit Error Counter
        unsigned                EWARN:1;            // [ R ] - Transmitter or Receiver is in Error State Warning
        unsigned                RXWARN:1;           // [ R ] - Receiver in Error State Warning (128 > RERRCNT ? 96)
        unsigned                TXWARN:1;           // [ R ] - Transmitter in Error State Warning (128 > TERRCNT ? 96)
        unsigned                RXBP:1;             // [ R ] - Receiver in Error State Bus Passive (RERRCNT ? 128)
        unsigned                TXBP:1;             // [ R ] - Transmitter in Error State Bus Passive (TERRCNT ? 128)
        unsigned                TXBO:1;             // [ R ] - Transmitter in Error State Bus OFF (TERRCNT ? 256)
    };
    struct 
    {
        uint32_t                v32;
    };
} can_trec_reg_t;
    
typedef union 
{
    struct 
    {
        unsigned                ICODE:7;            // [ R ] - Interrupt Flag Code bits (   1001000 = Invalid message received (IVRIF)
                                                    //                                      1000111 = CAN module mode change (MODIF)
                                                    //                                      1000110 = CAN timestamp timer (CTMRIF)
                                                    //                                      1000101 = Bus bandwidth error (SERRIF)
                                                    //                                      1000100 = Address error interrupt (SERRIF)
                                                    //                                      1000011 = Receive FIFO overflow interrupt (RBOVIF)
                                                    //                                      1000010 = Wake-up interrupt (WAKIF)
                                                    //                                      1000001 = Error Interrupt (CERRIF)
                                                    //                                      1000000 = No interrupt
                                                    //                                      0011111 = FIFO31 Interrupt (CiFSTAT<31> set)
                                                    //                                      ...
                                                    //                                      0000000 = FIFO0 Interrupt (CiFSTAT<0> set))
        unsigned                :1;
        unsigned                FILHIT:5;           // [ R ] - Filter Hit Number bit (11111 = Filter 31 / ... / 00000 = Filter 0)
        unsigned                :19;
    };
    struct 
    {
        uint32_t                v32;
    };
} can_vec_reg_t;

typedef union 
{
    struct 
    {
        unsigned                TBIF:1;             // [ R/W ] -  Transmit Buffer Interrupt Flag bit
        unsigned                RBIF:1;             // [ R/W ] -  Receive Buffer Interrupt Flag bit
        unsigned                CTMRIF:1;           // [ R/W ] -  CAN Timer Overflow Interrupt Flag bit
        unsigned                MODIF:1;            // [ R/W ] -  CAN Mode Change Interrupt Flag bit
        unsigned                :7;
        unsigned                RBOVIF:1;           // [ R/W ] -  Receive Buffer Overflow Interrupt Flag bit
        unsigned                SERRIF:1;           // [ R/W ] -  System Error Interrupt Flag bit
        unsigned                CERRIF:1;           // [ R/W ] -  CAN Bus Error Interrupt Flag bit
        unsigned                WAKIF:1;            // [ R/W ] -  CAN Bus Activity Wake-up Interrupt Flag bit
        unsigned                IVRIF:1;            // [ R/W ] -  Invalid Message Received Interrupt Flag bit
        
        unsigned                TBIE:1;             // [ R/W ] -  Transmit Buffer Interrupt Enable bit
        unsigned                RBIE:1;             // [ R/W ] -  Receive Buffer Interrupt Enable bit
        unsigned                CTMRIE:1;           // [ R/W ] -  CAN Timestamp Timer Interrupt Enable bit
        unsigned                MODIE:1;            // [ R/W ] -  Mode Change Interrupt Enable bit
        unsigned                :7;
        unsigned                RBOVIE:1;           // [ R/W ] -  Receive Buffer Overflow Interrupt Enable bit
        unsigned                SERRIE:1;           // [ R/W ] -  System Error Interrupt Enable bit
        unsigned                CERRIE:1;           // [ R/W ] -  CAN Bus Error Interrupt Enable bit
        unsigned                WAKIE:1;            // [ R/W ] -  CAN Bus Activity Wake-up Interrupt Enable bit
        unsigned                IVRIE:1;            // [ R/W ] -  Invalid Message Received Interrupt Enable bit
    };
    struct 
    {
        uint32_t                v32;
    };
} can_int_reg_t;

typedef union 
{
    struct 
    {
        unsigned                BRP:6;              // [ R/W ] - Baud Rate Prescaler bits (111111 = TQ = (2 x 64)/FSYS / 111110 = TQ = (2 x 63)/FSYS / ... / 000001 = TQ = (2 x 2)/FSYS / 000000 = TQ = (2 x 1)/FSYS)
        unsigned                SJW:2;              // [ R/W ] - Synchronization Jump Width bits (11 = Length is 4 x TQ / 10 = Length is 3 x TQ / 01 = Length is 2 x TQ / 00 = Length is 1 x TQ)
        unsigned                PRSEG:3;            // [ R/W ] - Propagation Time Segment bits (111 = Length is 8 x TQ / ... / 000 = Length is 1 x TQ)
        unsigned                SEG1PH:3;           // [ R/W ] - Phase Buffer Segment 1 bits (111 = Length is 8 x TQ / ... / 000 = Length is 1 x TQ)
        unsigned                SAM:1;              // [ R/W ] - Sample of the CAN Bus Line bit (1 = Bus line is sampled three times at the sample point / 0 = Bus line is sampled once at the sample point)
        unsigned                SEG2PHTS:1;         // [ R/W ] - Phase Segment 2 Time Select bit(1 = Freely programmable / 0 = Maximum of SEG1PH or Information Processing Time, whichever is greater)
        unsigned                SEG2PH:3;           // [ R/W ] - Phase Buffer Segment 2 bits (111 = Length is 8 x TQ / ... / 000 = Length is 1 x TQ)
        unsigned                :3;
        unsigned                WAKFIL:1;           // [ R/W ] - CAN Bus Line Filter Enable bit (1 = Use CAN bus line filter for wake-up / 0 = CAN bus line filter is not used for wake-up)
        unsigned                :9;
    };
    struct 
    {
        uint32_t                v32;
    };
} can_cfg_reg_t;

typedef union 
{
    struct 
    {
        unsigned                DNCNT:5;            // [ R/W ] - Device Net Filter Bit Number bits
        unsigned                :6;
        unsigned                CANBUSY:1;          // [ R ] - CAN Module is Busy bit (1 = The CAN module is active / 0 = The CAN module is completely disabled)
        unsigned                :1;
        unsigned                SIDL:1;             // [ R/W ] - CAN Stop in Idle bit (1 = CAN Stops operation when system enters Idle mode / 0 = CAN continues operation when system enters Idle mode)
        unsigned                :1;
        unsigned                PERIPHERAL_ENABLE:1;// [ R/W ] - CAN On bit (1 = CAN module is enabled / 0 = CAN module is disabled)
        unsigned                :4;
        unsigned                CANCAP:1;           // [ R/W ] - CAN Message Receive Time Stamp Timer Capture Enable bit (1 = CANTMR value is stored on valid message reception and is stored with the message / 0 = Disable CAN message receive time stamp timer capture and stop CANTMR to conserve power)
        unsigned                OPMOD:3;            // [ R ] - Operation Mode Status bits (     111 = Module is in Listen All Messages mode
                                                    //                                          100 = Module is in Configuration mode
                                                    //                                          011 = Module is in Listen-Only mode
                                                    //                                          010 = Module is in Loopback mode
                                                    //                                          001 = Module is in Disable mode
                                                    //                                          000 = Module is in Normal Operation mode)
        unsigned                REQOP:3;            // [ R/W ] - Request Operation Mode bits (  111 = Set Listen All Messages mode
                                                    //                                          100 = Set Configuration mode
                                                    //                                          011 = Set Listen-Only mode
                                                    //                                          010 = Set Loopback mode
                                                    //                                          001 = Set Disable mode
                                                    //                                          000 = Set Normal Operation mode)
        unsigned                ABAT:1;             // [ S/HC ] - Abort All Pending Transmissions bit (1 = Signal all transmit buffers to abort transmission / 0 = Module will clear this bit when all transmissions aborted)
        unsigned                :4;
    };
    struct 
    {
        uint32_t                v32;
    };
} can_con_reg_t;

typedef struct
{
    volatile can_fifocon_reg_t          CANFIFOCON;     // See union for more details
    volatile uint32_t                   CANFIFOCONCLR;
    volatile uint32_t                   CANFIFOCONSET;
    volatile uint32_t                   CANFIFOCONINV;
    
    volatile can_fifoint_reg_t          CANFIFOINT;     // See union for more details
    volatile uint32_t                   CANFIFOINTCLR;
    volatile uint32_t                   CANFIFOINTSET;
    volatile uint32_t                   CANFIFOINTINV;
    
    volatile uint32_t                   CANFIFOUA;      // [ R ] - CAN FIFO User Address 
    volatile uint32_t                   CANFIFOUACLR;
    volatile uint32_t                   CANFIFOUASET;
    volatile uint32_t                   CANFIFOUAINV;
    
    volatile uint32_t                   CANFIFOCI;      // [ R ] - CAN Side FIFO Message Index
    volatile uint32_t                   CANFIFOCICLR;
    volatile uint32_t                   CANFIFOCISET;
    volatile uint32_t                   CANFIFOCIINV;
} can_fifo_regs_t;

typedef struct
{
    volatile can_rxf_reg_t              CANRXF;         // See union for more details
    volatile uint32_t                   CANRXFCLR;
    volatile uint32_t                   CANRXFSET;
    volatile uint32_t                   CANRXFINV;
} can_rx_filter_reg_t;

typedef struct
{
    volatile uint8_t                    CANFLTCON[4];   // FSEL:5 [ R/W ] - FIFO Selection bits (11111 = Message matching filter is stored in FIFO buffer 31 / ... / 00000 = Message matching filter is stored in FIFO buffer 0)
                                                        // MSEL:2 [ R/W ] - Filter x Mask Select bits (11 = Acceptance Mask 3 selected / 10 = Acceptance Mask 2 selected / 01 = Acceptance Mask 1 selected / 00 = Acceptance Mask 0 selected)
                                                        // FLTEN:1 [ R/W ] - Filter x Enable bit
    volatile uint32_t                   CANFLTCONCLR;
    volatile uint32_t                   CANFLTCONSET;
    volatile uint32_t                   CANFLTCONINV;
} can_filter_control_reg_t;

typedef struct
{
    volatile can_rxm_reg_t              CANRXM;         // See union for more details
    volatile uint32_t                   CANRXMCLR;
    volatile uint32_t                   CANRXMSET;
    volatile uint32_t                   CANRXMINV;
} can_filter_mask_reg_t;

typedef struct
{
    // Module and CAN Bit Rate Configuration Registers
    volatile can_con_reg_t              CANCON;         // See union for more details
	volatile uint32_t                   CANCONCLR; 
	volatile uint32_t                   CANCONSET;
	volatile uint32_t                   CANCONINV;
    
    volatile can_cfg_reg_t              CANCFG;         // See union for more details
    volatile uint32_t                   CANCFGCLR;
    volatile uint32_t                   CANCFGSET;
    volatile uint32_t                   CANCFGINV;
    // ------------------------------------------------
    // Interrupt and Status Registers
    volatile can_int_reg_t              CANINT;         // See union for more details
    volatile uint32_t                   CANINTCLR;
    volatile uint32_t                   CANINTSET;
    volatile uint32_t                   CANINTINV;
    
    volatile can_vec_reg_t              CANVEC;         // See union for more details
    volatile uint32_t                   CANVECCLR;
    volatile uint32_t                   CANVECSET;
    volatile uint32_t                   CANVECINV;
    
    volatile can_trec_reg_t             CANTREC;        // See union for more details
    volatile uint32_t                   CANTRECCLR;
    volatile uint32_t                   CANTRECSET;
    volatile uint32_t                   CANTRECINV;

	volatile uint32_t                   CANFSTAT;       // [ R ] - FIFOn Interrupt Pending (1 = One or more enabled FIFO interrupts are pending / 0 = No FIFO interrupts are pending)
	volatile uint32_t                   CANFSTATCLR;
	volatile uint32_t                   CANFSTATSET;
	volatile uint32_t                   CANFSTATINV;

	volatile uint32_t                   CANRXOVF;       // [ R ] - FIFOn Receive Overflow Interrupt Pending (1 = FIFO has overflowed / 0 = FIFO has not overflowed)
	volatile uint32_t                   CANRXOVFCLR;
	volatile uint32_t                   CANRXOVFSET;
	volatile uint32_t                   CANRXOVFINV;

	volatile can_tmr_reg_t              CANTMR;         // See union for more details
	volatile uint32_t                   CANTMRCLR;
	volatile uint32_t                   CANTMRSET;
	volatile uint32_t                   CANTMRINV;
    // ------------------------------------------------
    // Mask and Filter Configuration Registers
    volatile can_filter_mask_reg_t      can_filter_mask_regs[CAN_NUMBER_OF_MASKS];              // See union for more details
    
    volatile can_filter_control_reg_t   can_filter_control_regs[CAN_NUMBER_OF_FILTER_CONTROLS]; // See union for more details
    
    volatile can_rx_filter_reg_t        can_rx_filter_regs[CAN_NUMBER_OF_FILTERS];              // See union for more details
    // ------------------------------------------------
    // CAN Module Control Registers
    volatile uint32_t                   CANFIFOBA;      // [ R/W ] - CAN FIFO Base Address
	volatile uint32_t                   CANFIFOBACLR;
	volatile uint32_t                   CANFIFOBASET;
	volatile uint32_t                   CANFIFOBAINV; 
    
    volatile can_fifo_regs_t            can_fifo_regs[CAN_NUMBER_OF_CHANNELS];                  // See union for more details
    
} can_registers_t;

typedef union 
{
    struct 
    {
        uint8_t                         BYTE4;
        uint8_t                         BYTE5;
        uint8_t                         BYTE6;
        uint8_t                         BYTE7;
    };
    struct 
    {
        uint32_t                        v32;
    };
} can_message_buffer_data1_t;

typedef union 
{
    struct 
    {
        uint8_t                         BYTE0;
        uint8_t                         BYTE1;
        uint8_t                         BYTE2;
        uint8_t                         BYTE3;
    };
    struct 
    {
        uint32_t                        v32;
    };
} can_message_buffer_data0_t;

typedef union 
{
    struct 
    {
        unsigned                        DLC:4;          // Data Length Code bits (1xxx = Module will transmit 8 bytes / 0111 = 7 bytes of data will be transmitted / ... / 0001 = 1 byte of data will be transmitted / 0000 = 0 bytes of data will be transmitted)
        unsigned                        RB0:1;          // Reserved bit 0. The user application must set this bit to ?0? per the CAN Specification 2.0B.
        unsigned                        :3;
        unsigned                        RB1:1;          // Reserved bit 1. The user application must set this bit to ?0? per the CAN Specification 2.0B.
        unsigned                        RTR:1;          // Remote Transmission Request bit (1 = Message is a remote transmission request / 0 = Message is not a remote transmission request)
        unsigned                        EID:18;         // Extended Identifier bits
        unsigned                        IDE:1;          // Extended Identifier bit (1 = Message will transmit extended identifier / 0 = Message will transmit standard identifier)
        unsigned                        SRR:1;          // Substitute Remote Request bit (In case of a standard message format (IDE = 0), this bit is don?t care. / In case of an extended message format (IDE = 1), this bit should always be set.)
        unsigned                        :2;
    };
    struct 
    {
        uint32_t                        v32;
    };
} can_message_buffer_eid_t;

typedef union 
{
    struct 
    {
        unsigned                        SID:11;         // Standard ID 11 bits
        unsigned                        :21;
    };
    struct 
    {
        uint32_t                        v32;
    };
} can_message_buffer_sid_t;

typedef struct
{
    can_message_buffer_sid_t   msg_sid;
    can_message_buffer_eid_t   msg_eid;
    can_message_buffer_data0_t msg_data_0_3;
    can_message_buffer_data1_t msg_data_4_7;
} can_message_buffer_t;

typedef enum
{
    CAN_READ_FRAME              = 1,
    CAN_WRITE_FRAME             = 0,
            
    CAN_STD_ID                  = 0,
    CAN_XTD_ID                  = 1,
    
    CAN_DATA_0_BYTE             = 0,
    CAN_DATA_1_BYTE             = 1,
    CAN_DATA_2_BYTES            = 2,
    CAN_DATA_3_BYTES            = 3,
    CAN_DATA_4_BYTES            = 4,
    CAN_DATA_5_BYTES            = 5,
    CAN_DATA_6_BYTES            = 6,
    CAN_DATA_7_BYTES            = 7,
    CAN_DATA_8_BYTES            = 8            
} CAN_FRAME_SETUP;

typedef struct
{
    can_message_buffer_t        frame;
    bool                        is_receive_updated;
    bool                        force_transfer;
    bool                        read_write_type;
    uint64_t                    period;
    uint64_t                    tick;
} can_frame_params_t;

#define CAN_MESSAGE_BUFFER_INSTANCE(_id, _extended_id, _data_length)    \
{                                                                       \
	.msg_sid.SID = _extended_id ? ((_id >> 18) & 0x7ff) : (_id & 0x7ff),\
    .msg_eid.DLC = _data_length,                                        \
    .msg_eid.RB0 = 0,                                                   \
    .msg_eid.RB1 = 0,                                                   \
    .msg_eid.RTR = 0,                                                   \
    .msg_eid.EID = _extended_id ? (_id & 0x3ffff) : 0,                  \
    .msg_eid.IDE = _extended_id,                                        \
    .msg_eid.SRR = 0,                                                   \
    .msg_data_0_3 = 0,                                                  \
    .msg_data_4_7 = 0                                                   \
}

#define CAN_FRAME_INSTANCE(_read_write_type, _id, _extended_id, _data_length, _period)      \
{                                                                                   \
	.frame = CAN_MESSAGE_BUFFER_INSTANCE(_id, _extended_id, _data_length),          \
    .is_receive_updated = false,                                                    \
    .force_transfer = false,                                                        \
    .read_write_type = _read_write_type,                                            \
    .period = _period,                                                              \
    .tick = 0                                                                       \
}

#define CAN_LINK_STRUCTURE_TO_FRAME(_name, _can_frame, _structure_t)        static _structure_t * _name = (_structure_t *) &_can_frame.frame.msg_data_0_3.BYTE0;
#define CAN_FRAME_TX_DEF(_name, _id, _extended_id, _data_length, _period)   CAN_FRAME_DEF(_name, CAN_WRITE_FRAME, _id, _extended_id, _data_length, _period)
#define CAN_FRAME_RX_DEF(_name, _id, _extended_id)                          CAN_FRAME_DEF(_name, CAN_READ_FRAME, _id, _extended_id, 0, 0)
#define CAN_FRAME_DEF(_name, _read_write_type, _id, _extended_id, _data_length, _period)    \
static can_frame_params_t _name = CAN_FRAME_INSTANCE(_read_write_type, _id, _extended_id, _data_length, _period)

typedef struct
{    
    bool                        is_init_done;
    CAN_MODULE                  id;
    CAN_BUS_SPEED               bus_speed;
    _io_t                       chip_enable;
    bool                        set_auto_bit_timing;
    void                        **p_frames;
    uint8_t                     number_of_frames;
    uint64_t                    tick;
} can_params_t;

#define CAN_PARAMS_INSTANCE(_can_module, _bus_speed, _set_auto_bit_timing, _io_port, _io_indice, _p_frames, _number_of_frames)    \
{                                                                                   \
	.is_init_done = false,                                                          \
    .id = _can_module,                                                              \
    .bus_speed = _bus_speed,                                                        \
    .chip_enable = { _io_port, _io_indice },                                        \
    .set_auto_bit_timing = _set_auto_bit_timing,                                    \
    .p_frames = (void *) _p_frames,                                                 \
    .number_of_frames = _number_of_frames,                                          \
    .tick = 0                                                                       \
}

#define CAN_DEF(_name, _can_module, _bus_speed, _set_auto_bit_timing, _chip_enable_pin, ...)                \
static void * _name ## _p_can_frames_ram_allocation[COUNT_ARGUMENTS( __VA_ARGS__ )] = { __VA_ARGS__ };      \
static can_params_t _name = CAN_PARAMS_INSTANCE(_can_module, _bus_speed, _set_auto_bit_timing, __PORT(_chip_enable_pin), __INDICE(_chip_enable_pin), _name ## _p_can_frames_ram_allocation, COUNT_ARGUMENTS( __VA_ARGS__ ))

void can_tasks(can_params_t *var);

void can_interrupt_handler(CAN_MODULE id);

#endif
   