#ifndef __DEF_ERRORS
#define __DEF_ERRORS

typedef enum
{
    __ERROR_DMA_NO_MORE_FREE_CHANNEL        = 1,
    __ERROR_GROVE_MOTOR_NEW_DEVICE_ADDRESS  = 2,
            
    __ERROR_MAX_FLAGS                       = 255
} __ERRORS;

#define ERROR(code_error)                   __errors(code_error)

void __errors(__ERRORS code_error);

#endif
