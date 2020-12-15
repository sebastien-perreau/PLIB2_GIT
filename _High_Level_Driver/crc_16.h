#ifndef __DEF_CRC_16
#define __DEF_CRC_16

#define crc_16(p_data, length)              crc_16_modbus(p_data, length)
#define crc_16_modbus(p_data, length)       crc16_fast_poly_0x8005(0xffff, true, true, 0x0000, p_data, length)
#define crc_16_usb(p_data, length)          crc16_fast_poly_0x8005(0xffff, true, true, 0xffff, p_data, length)
#define crc_16_maxim(p_data, length)        crc16_fast_poly_0x8005(0x0000, true, true, 0xffff, p_data, length)
#define crc_16_arc(p_data, length)          crc16_fast_poly_0x8005(0x0000, true, true, 0x0000, p_data, length)
#define crc_16_buypass(p_data, length)      crc16_fast_poly_0x8005(0x0000, false, false, 0x0000, p_data, length)
#define crc_16_dds_110(p_data, length)      crc16_fast_poly_0x8005(0x800d, false, false, 0x0000, p_data, length)

uint16_t crc16_fast_poly_0x8005(uint16_t seed, bool reflected_input, bool reflected_output, uint16_t xorout, void * p_data, uint16_t length);

#endif
