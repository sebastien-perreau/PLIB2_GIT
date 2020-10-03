#ifndef __DEF_DMA
#define __DEF_DMA

#define DMA_MAX_TRANSFER_SIZE               65536
#define DMA_MAX_SRC_SIZE                    DMA_MAX_TRANSFER_SIZE
#define DMA_MAX_DST_SIZE                    DMA_MAX_TRANSFER_SIZE
#define DMA_MAX_CELL_SIZE                   DMA_MAX_TRANSFER_SIZE

typedef enum 
{
    DMA0                                    = 0,
    DMA1,
    DMA2,
    DMA3,
    DMA4,
    DMA5,
    DMA6,
    DMA7,
    DMA_NUMBER_OF_MODULES
} dma_module_type_t;

typedef enum
{
    DMA_CONT_PRIO_0                         = 0x00000000,       // Lowest priority
    DMA_CONT_PRIO_1                         = 0x00000001,
    DMA_CONT_PRIO_2                         = 0x00000002,
    DMA_CONT_PRIO_3                         = 0x00000003,       // Highest priority
            
    DMA_CONT_AUTO_ENABLE                    = 0x00000010,       // Channel is continuously enabled, and not automatically disabled after a block transfer is complete
    DMA_CONT_CHAIN_HIGHER                   = 0x00000020,       // Allow channel to be chained & chain to channel higher in natural priority (CH1 will be enabled by CH0 transfer complete)
    DMA_CONT_CHAIN_LOWER                    = 0x00000120,       // Allow channel to be chained & chain to channel lower in natural priority (CH1 will be enabled by CH2 transfer complete)    
            
    DMA_CONT_CHANNEL_ENABLE                 = 0x00000080,       // Make the channel ON
    DMA_CONT_CHANNEL_DISABLE                = 0x00000000,       // Make the channel OFF
            
    DMA_CONT_PATTERN_2_BYTES                = 0x00000800,       // Pattern = 2 bytes length
    DMA_CONT_PATTERN_1_BYTE                 = 0x00000000,       // Pattern = 1 byte length
} dma_channel_control_type_t;

typedef enum
{
    DMA_EVT_FORCE_TRANSFER                  = 0x00000080,
    DMA_EVT_ABORD_TRANSFER                  = 0x00000040,
            
    DMA_EVT_ABORD_TRANSFER_ON_PATTERN_MATCH = 0x00000020,
    DMA_EVT_START_TRANSFER_ON_IRQ           = 0x00000010,
    DMA_EVT_ABORD_TRANSFER_ON_IRQ           = 0x00000008,            
    DMA_EVT_NONE                            = 0x00000000
} dma_channel_event_type_t;

typedef enum
{
    // value 32 bits = 0x00[interrupt enable bits 2 bytes]00[interrupt flag bits 2 bytes]
    DMA_INT_ADDRESS_ERROR                   = 0x00010001,
    DMA_INT_TRANSFER_ABORD                  = 0x00020002,
    DMA_INT_CELL_TRANSFER_DONE              = 0x00040004,
    DMA_INT_BLOCK_TRANSFER_DONE             = 0x00080008,
    DMA_INT_DEST_HALF_FULL                  = 0x00100010,
    DMA_INT_DEST_FULL                       = 0x00200020,
    DMA_INT_SRC_HALF_FULL                   = 0x00400040,
    DMA_INT_SRC_FULL                        = 0x00800080,
            
    DMA_INT_NONE                            = 0x00000000,
    DMA_INT_ALL                             = 0x00ff00ff
} dma_channel_interrupt_type_t;

typedef enum
{
    DMA_FLAG_ADDRESS_ERROR                  = 0x00000001,
    DMA_FLAG_TRANSFER_ABORD                 = 0x00000002,
    DMA_FLAG_CELL_TRANSFER_DONE             = 0x00000004,
    DMA_FLAG_BLOCK_TRANSFER_DONE            = 0x00000008,
    DMA_FLAG_DEST_HALF_FULL                 = 0x00000010,
    DMA_FLAG_DEST_FULL                      = 0x00000020,
    DMA_FLAG_SRC_HALF_FULL                  = 0x00000040,
    DMA_FLAG_SRC_FULL                       = 0x00000080,
            
    DMA_FLAG_ALL                            = 0x000000ff
} dma_channel_flags_type_t;

typedef enum
{
    DMA_CRC_CALCULATED_LSB_FIRST            = 0x01000000,
    DMA_CRC_CALCULATED_MSB_FIRST            = 0,
            
    DMA_CRC_CON_ENABLE                      = 0x00000080,
    DMA_CRC_CON_DISABLE                     = 0,
            
    DMA_CRC_CON_APPEND_ENABLE               = 0x00000040,
    DMA_CRC_CON_APPEND_DISABLE              = 0,
    
    DMA_CRC_CON_TYPE_IP_HEADER              = 0x00000020,
    DMA_CRC_CON_TYPE_LFSR                   = 0
} dma_crc_con_type_t;

typedef struct
{
    const void      *src_start_addr; 
    const void      *dst_start_addr; 
    uint16_t        src_size;
    uint16_t        dst_size;
    uint16_t        cell_size;
    uint16_t        pattern_data;
} dma_channel_transfer_t;

typedef struct
{
    volatile uint32_t DCHCON;
    volatile uint32_t DCHCONCLR;
    volatile uint32_t DCHCONSET;
    volatile uint32_t DCHCONINV;
    
    volatile uint32_t DCHECON;
    volatile uint32_t DCHECONCLR;
    volatile uint32_t DCHECONSET;
    volatile uint32_t DCHECONINV;
    
    volatile uint32_t DCHINT;
    volatile uint32_t DCHINTCLR;
    volatile uint32_t DCHINTSET;
    volatile uint32_t DCHINTINT;
    
    volatile uint32_t DCHSSA;
    volatile uint32_t DCHSSACLR;
    volatile uint32_t DCHSSASET;
    volatile uint32_t DCHSSAINV;
    
    volatile uint32_t DCHDSA;
    volatile uint32_t DCHDSACLR;
    volatile uint32_t DCHDSASET;
    volatile uint32_t DCHDSAINV;
    
    volatile uint32_t DCHSSIZ;
    volatile uint32_t DCHSSIZCLR;
    volatile uint32_t DCHSSIZSET;
    volatile uint32_t DCHSSIZINV;
    
    volatile uint32_t DCHDSIZ;
    volatile uint32_t DCHDSIZCLR;
    volatile uint32_t DCHDSIZSET;
    volatile uint32_t DCHDSIZINV;
    
    volatile uint32_t DCHSPTR;
    volatile uint32_t DCHSPTRCLR;
    volatile uint32_t DCHSPTRSET;
    volatile uint32_t DCHSPTRINV;
    
    volatile uint32_t DCHDPTR;
    volatile uint32_t DCHDPTRCLR;
    volatile uint32_t DCHDPTRSET;
    volatile uint32_t DCHDPTRINV;
    
    volatile uint32_t DCHCSIZ;
    volatile uint32_t DCHCSIZCLR;
    volatile uint32_t DCHCSIZSET;
    volatile uint32_t DCHCSIZINV;
    
    volatile uint32_t DCHCPTR;
    volatile uint32_t DCHCPTRCLR;
    volatile uint32_t DCHCPTRSET;
    volatile uint32_t DCHCPTRINV;
    
    volatile uint32_t DCHDAT;
    volatile uint32_t DCHDATCLR;
    volatile uint32_t DCHDATSET;
    volatile uint32_t DCHDATINV;
} dma_channel_registers_t;

typedef struct
{
    uint32_t            polynomial_value;
    uint8_t             polynomial_order;
    uint32_t            seed;
    bool                reflected_io;
    uint32_t            xorout;
} dma_crc_t;

typedef void (*dma_event_handler_t)(uint8_t id, dma_channel_flags_type_t flags);

dma_module_type_t dma_init( dma_event_handler_t evt_handler, 
                            dma_channel_control_type_t dma_channel_control,
                            dma_channel_interrupt_type_t dma_channel_interrupt,
                            dma_channel_event_type_t dma_channel_event,
                            uint8_t irq_num_tx_start,
                            uint8_t irq_num_tx_abord);
uint32_t dma_suspend();
void dma_resume(uint32_t suspend_status);
void dma_set_channel_event_control(dma_module_type_t id, dma_channel_event_type_t dma_channel_event);
void dma_set_transfer_params(dma_module_type_t id, dma_channel_transfer_t * channel_transfer);
void dma_channel_enable(dma_module_type_t id, bool enable, bool force_transfer);
void dma_abord_transfer(dma_module_type_t id);
bool dma_channel_is_enable(dma_module_type_t id);
uint16_t dma_get_index_cell_pointer(dma_module_type_t id);
dma_channel_flags_type_t dma_get_flags(dma_module_type_t id);
void dma_clear_flags(dma_module_type_t id, dma_channel_flags_type_t flags);

const uint8_t dma_get_irq(dma_module_type_t id);
void dma_interrupt_handler(dma_module_type_t id);


void dma_crc_init(uint32_t polynomial_value, uint8_t polynomial_order, uint32_t seed, bool reflected_io, uint32_t xorout);
void dma_crc_execute(void * p_data, uint32_t length);
bool dma_crc_is_calculated();
uint32_t dma_crc_read();
	
#endif
