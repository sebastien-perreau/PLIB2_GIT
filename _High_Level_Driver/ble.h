#ifndef __BLE_H
#define __BLE_H

#define ID_NONE								0xfe
#define ID_BOOT_MODE                		0x00
#define ID_SECURITY_MODE                    0x01
#define ID_NAME								0x02
#define ID_SOFTWARE_VERSION                 0x03
#define ID_PA_LNA							0x04
#define ID_LED_STATUS						0x05
#define ID_BLE_ADV_INTERVAL					0x06
#define ID_BLE_ADV_TIMEOUT					0x07
#define ID_HARDWARE_STATUS					0x08
#define ID_BLE_CONNECTION_STATUS			0x09
#define ID_BLE_PARAMETERS_STATUS			0x0a
#define ID_BLE_CHARACTERISTICS_PROPERTIES	0x0b

#define ID_BLE_CONN_PARAMS     				0x20
#define ID_BLE_PHY_PARAM   					0x21
#define ID_BLE_ATT_MTU_PARAM				0x22
#define ID_BLE_DATA_LENGTH_PARAM  			0x23
#define ID_BLE_CONN_EVT_LENGTH_EXT_PARAM  	0x24

#define ID_SOFTWARE_RESET					0xff

#define ID_CHAR_SPC_STATUS					0x10
#define ID_CHAR_THROUGHPUT					0x11
#define ID_CHAR_BUFFER              		0x30

#define MSEC_TO_UNITS(TIME, RESOLUTION)     (((TIME) * 1000) / (RESOLUTION))
#define UNIT_0_625_MS                       625
#define UNIT_1_25_MS                        1250
#define UNIT_10_MS                          10000

#define BLE_GAP_PHY_1MBPS                   0x01
#define BLE_GAP_PHY_2MBPS                   0x02

#define BLE_SECURITY_ENABLED                1
#define BLE_SECURITY_DISABLED               0

typedef enum
{
	RESET_BLE_PICKIT 						= 1,
	RESET_PIC32_HOST						= 2,
	RESET_BOTH								= 3
} ble_pickit_reset_type_t;

typedef enum
{
    UART_NO_MESSAGE                         = 0,
    UART_ACK_MESSAGE,
    UART_NAK_MESSAGE,
    UART_NEW_MESSAGE
} ble_pickit_uart_message_type_t;

typedef struct
{
    uint8_t                                 in_data[242];
    uint8_t                                 in_length;
    bool                                    in_is_updated;
    uint8_t                                 out_data[242];
    uint8_t                                 out_length;
} ble_pickit_char_buffer_t;

typedef struct
{
    uint8_t                                 time_x20ms;
    uint64_t                                tick;
} ble_pickit_char_spc_t;

typedef union
{
    struct
    {
        unsigned                            security_mode:1;
        unsigned                            name:1;
        unsigned                            software_version:1;
        unsigned                            pa_lna:1;
        unsigned                            led_status:1;
        unsigned                            adv_interval:1;
        unsigned                            adv_timeout:1;
		unsigned							software_reset:1;
		unsigned							reset_requested:1;               
        
        unsigned                            ble_pref_conn_params:1;
        unsigned                            ble_pref_phy_param:1;
        unsigned                            ble_pref_att_mtu_param:1;
        unsigned                            ble_pref_data_length_param:1;
        unsigned                            ble_pref_conn_evt_length_ext_param:1;
        
        unsigned                            notif_app_spc:1;
        unsigned                            notif_app_buffer:1;
    };
    struct
    {
        uint32_t                            w;
    };
} ble_pickit_flags_t;

typedef struct
{
    ble_pickit_uart_message_type_t          message_type;
	bool                                    receive_in_progress;
	uint8_t                                 rx_buffer[256];
	uint16_t                                index;
    uint16_t                                old_index;
	uint64_t                                tick;
} ble_pickit_serial_uart_t;

typedef union
{
    struct
    {
        unsigned                            broadcast:1;
        unsigned                            read:1;
        unsigned                            write_wo_resp:1;
        unsigned                            write:1;
        unsigned                            notify:1;
        unsigned                            indicate:1;
        unsigned                            auth_signed_wr:1;
    };
    struct
    {
        uint8_t                             b;
    };
} ble_pickit_characteristic_properties_t;

typedef struct
{
    ble_pickit_characteristic_properties_t  properties;
	bool									is_notify_enabled;
} ble_pickit_characteristic_status_t;

typedef struct
{
    bool                                    is_characteristics_status_updated;
	ble_pickit_characteristic_status_t      _0x1501;
	ble_pickit_characteristic_status_t      _0x1503;	
} ble_pickit_characteristics_status_t;

typedef struct
{
    uint16_t                                min_conn_interval;
    uint16_t                                max_conn_interval;
    uint16_t                                slave_latency;
    uint16_t                                conn_sup_timeout;
} ble_gap_conn_params_t;

typedef struct
{
    bool                                    is_gap_params_updated;          // Only used for "current_params"
	ble_gap_conn_params_t                   conn_params;
	uint8_t                                 phy;
	uint8_t                                 att_mtu;
    uint8_t                                 data_length;
    uint8_t                                 conn_evt_len_ext;
	uint32_t                                adv_interval;
	uint32_t                                adv_timeout;
} ble_pickit_gap_params_t;

typedef struct
{
    bool                                    is_connection_status_updated;
	bool									is_in_advertising_mode;
	bool									is_connected_to_a_central;
} ble_pickit_connection_status_t;

typedef struct
{
    bool                                    is_hardware_status_updated;
	bool									pa_lna_enable;
	bool									led_enable;
} ble_pickit_hardware_status_t;

typedef struct
{
	bool									enable;
	bool									is_lock;
} ble_pickit_security_t;

typedef struct
{
	ble_pickit_reset_type_t                 reset_type;
    char                                    software_version[8];
    char                                    name[20];
	ble_pickit_security_t                   security_connection;
} ble_pickit_device_infos_t;

typedef struct
{
    ble_pickit_device_infos_t               device;
	ble_pickit_hardware_status_t			hardware;
	ble_pickit_connection_status_t			connection;
	ble_pickit_gap_params_t					preferred_params;
	ble_pickit_gap_params_t					current_params;
	ble_pickit_characteristics_status_t     characteristics;
} ble_pickit_status_t;

typedef struct
{
    ble_pickit_status_t                     status;
	ble_pickit_serial_uart_t                uart;   
    ble_pickit_flags_t                      flags;
    ble_pickit_char_spc_t                   app_spc;
    ble_pickit_char_buffer_t                app_buffer;
} ble_pickit_t;


#define BLE_PICKIT_CONN_PARAMS_INSTANCE()						\
{																\
	.min_conn_interval 	= MSEC_TO_UNITS(15, UNIT_1_25_MS),		\
	.max_conn_interval 	= MSEC_TO_UNITS(15, UNIT_1_25_MS),		\
	.slave_latency 		= 0,									\
	.conn_sup_timeout 	= MSEC_TO_UNITS(4000, UNIT_10_MS)		\
}

#define BLE_PICKIT_PREFERRED_PARAMS_INSTANCE()					\
{																\
    .is_gap_params_updated = false,                             \
	.conn_params = BLE_PICKIT_CONN_PARAMS_INSTANCE(),			\
	.phy = BLE_GAP_PHY_2MBPS,                                   \
	.att_mtu = 247,                                             \
	.data_length = 251,                                         \
	.conn_evt_len_ext = true,                                   \
	.adv_interval = MSEC_TO_UNITS(100, UNIT_0_625_MS),          \
	.adv_timeout = 18000                                        \
}

#define BLE_PICKIT_DEVICE_INFOS_INSTANCE(_name, _security)      \
{                                                               \
	.reset_type = 0,                                            \
    .software_version = {"x.xx.xx"},                            \
    .name = {_name},                                            \
    .security_connection = { _security, 0}                      \
}

#define BLE_PICKIT_STATUS_INSTANCE(_name, _security)            \
{                                                       		\
	.device = BLE_PICKIT_DEVICE_INFOS_INSTANCE(_name, _security),\
	.hardware = {false, false, true},							\
	.connection = {0},											\
	.preferred_params = BLE_PICKIT_PREFERRED_PARAMS_INSTANCE(),	\
	.current_params = {0, {0}, 0, 0, 0, 0, 0, 0},				\
	.characteristics = {0, {{0}}, {{0}}}						\
}

#define BLE_PICKIT_INSTANCE(_name, _security)                   \
{                                                               \
    .status = BLE_PICKIT_STATUS_INSTANCE(_name, _security),     \
	.uart = {0},                                                \
    .flags = {{0}},                                             \
    .app_spc = {0},                                             \
    .app_buffer = {0},                                          \
}

#define BLE_PICKIT_DEF(_var, _name, _security)                  \
static ble_pickit_t _var = BLE_PICKIT_INSTANCE(_name, _security)

typedef void (*p_ble_function)(uint8_t *buffer);

void ble_init(UART_MODULE uart_id, uint32_t data_rate, ble_pickit_t * p_ble_pickit);
void ble_stack_tasks();

extern __inline__ void __attribute__((always_inline)) ble_security_enabled(ble_pickit_t * p_ble_pickit)
{
    p_ble_pickit->status.device.security_connection.enable = true;
    p_ble_pickit->flags.security_mode = 1;
}

extern __inline__ void __attribute__((always_inline)) ble_security_disabled(ble_pickit_t * p_ble_pickit)
{
    p_ble_pickit->status.device.security_connection.enable = false;
    p_ble_pickit->flags.security_mode = 1;
}

extern __inline__ void __attribute__((always_inline)) ble_set_name(ble_pickit_t * p_ble_pickit, char *name, uint8_t length)
{
    memcpy(p_ble_pickit->status.device.name, name, length);
    p_ble_pickit->status.device.name[length] = '\0';
    p_ble_pickit->status.device.reset_type = RESET_BLE_PICKIT;
    p_ble_pickit->flags.reset_requested = 1;
}

extern __inline__ void __attribute__((always_inline)) ble_pa_lna_enabled(ble_pickit_t * p_ble_pickit)
{
    p_ble_pickit->status.hardware.pa_lna_enable = true;
    p_ble_pickit->status.device.reset_type = RESET_BLE_PICKIT;
    p_ble_pickit->flags.reset_requested = 1;
}

extern __inline__ void __attribute__((always_inline)) ble_pa_lna_disabled(ble_pickit_t * p_ble_pickit)
{
    p_ble_pickit->status.hardware.pa_lna_enable = false;
    p_ble_pickit->status.device.reset_type = RESET_BLE_PICKIT;
    p_ble_pickit->flags.reset_requested = 1;
}

extern __inline__ void __attribute__((always_inline)) ble_led_status_enabled(ble_pickit_t * p_ble_pickit)
{
    p_ble_pickit->status.hardware.led_enable = true;
    p_ble_pickit->flags.led_status = 1;
}

extern __inline__ void __attribute__((always_inline)) ble_led_status_disabled(ble_pickit_t * p_ble_pickit)
{
    p_ble_pickit->status.hardware.led_enable = false;
    p_ble_pickit->flags.led_status = 1;
}

#endif
