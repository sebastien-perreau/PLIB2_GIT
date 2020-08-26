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
} DMA_MODULE;

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
} DMA_CHANNEL_CONTROL;

typedef enum
{
    DMA_EVT_FORCE_TRANSFER                  = 0x00000080,
    DMA_EVT_ABORD_TRANSFER                  = 0x00000040,
            
    DMA_EVT_ABORD_TRANSFER_ON_PATTERN_MATCH = 0x00000020,
    DMA_EVT_START_TRANSFER_ON_IRQ           = 0x00000010,
    DMA_EVT_ABORD_TRANSFER_ON_IRQ           = 0x00000008,            
    DMA_EVT_NONE                            = 0x00000000
} DMA_CHANNEL_EVENT;

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
} DMA_CHANNEL_INTERRUPT;

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
} DMA_CHANNEL_FLAGS;

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

typedef void (*dma_event_handler_t)(uint8_t id, DMA_CHANNEL_FLAGS flags);

extern __inline__ unsigned int __attribute__((always_inline)) _VirtToPhys2(const void* p)
{
	return (int)p<0?((int)p&0x1fffffffL):(unsigned int)((unsigned char*)p+0x40000000L);
}

void dma_init(  DMA_MODULE id, 
                dma_event_handler_t evt_handler, 
                DMA_CHANNEL_CONTROL dma_channel_control,
                DMA_CHANNEL_INTERRUPT dma_channel_interrupt,
                DMA_CHANNEL_EVENT dma_channel_event,
                uint8_t irq_num_tx_start,
                uint8_t irq_num_tx_abord);
uint32_t dma_suspend();
void dma_resume(uint32_t suspend_status);
DMA_MODULE dma_get_free_channel();
void dma_set_channel_event_control(DMA_MODULE id, DMA_CHANNEL_EVENT dma_channel_event);
void dma_set_transfer_params(DMA_MODULE id, dma_channel_transfer_t * channel_transfer);
void dma_channel_enable(DMA_MODULE id, bool enable, bool force_transfer);
void dma_abord_transfer(DMA_MODULE id);
bool dma_channel_is_enable(DMA_MODULE id);
uint16_t dma_get_index_cell_pointer(DMA_MODULE id);
DMA_CHANNEL_FLAGS dma_get_flags(DMA_MODULE id);
void dma_clear_flags(DMA_MODULE id, DMA_CHANNEL_FLAGS flags);

const uint8_t dma_get_irq(DMA_MODULE id);
void dma_interrupt_handler(DMA_MODULE id);
	
#endif
