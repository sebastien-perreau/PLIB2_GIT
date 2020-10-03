/*********************************************************************
*	BLE driver
*	Author : Sébastien PERREAU
*
*	version: 6.20.11
*********************************************************************/

#include "../PLIB2.h"

static ble_pickit_t * p_ble_pickit;
static acquisitions_params_t *p_acquisitions;
static UART_MODULE m_uart_id = UART_NUMBER_OF_MODULES;
static dma_module_type_t m_dma_id = DMA_NUMBER_OF_MODULES;
static dma_channel_transfer_t dma_tx = {NULL, NULL, 0, 0, 0, 0x0000};

static const char __ack[] = "ACK";
static const char __nak[] = "NAK";

static void _security_mode(uint8_t *buffer);
static void _name(uint8_t *buffer);
static void _software_version(uint8_t *buffer);
static void _pa_lna(uint8_t *buffer);
static void _led_status(uint8_t *buffer);
static void _adv_interval(uint8_t *buffer);
static void _adv_timeout(uint8_t *buffer);

static void _conn_params(uint8_t *buffer);
static void _phy_param(uint8_t *buffer);
static void _att_mtu_param(uint8_t *buffer);
static void _data_length_param(uint8_t *buffer);
static void _conn_evt_length_ext_param(uint8_t *buffer);

static void _reset_request(uint8_t *buffer);
static void _app_buffer(uint8_t *buffer);
static void _app_spc(uint8_t *buffer);

static uint8_t vsd_outgoing_message_uart(p_ble_function ptr);

static void __boot_sequence()
{
    p_ble_pickit->flags.security_mode = 1;
    p_ble_pickit->flags.name = 1;
    p_ble_pickit->flags.software_version = 1;
    p_ble_pickit->flags.pa_lna = 1;
    p_ble_pickit->flags.led_status = 1;
    p_ble_pickit->flags.adv_interval = 1;
    p_ble_pickit->flags.adv_timeout = 1;
    
    p_ble_pickit->flags.ble_pref_conn_params = 1;
    p_ble_pickit->flags.ble_pref_phy_param = 1;
    p_ble_pickit->flags.ble_pref_att_mtu_param = 1;
    p_ble_pickit->flags.ble_pref_data_length_param = 1;
    p_ble_pickit->flags.ble_pref_conn_evt_length_ext_param = 1;
}

static void ble_uart_event_handler(uint8_t id, IRQ_EVENT_TYPE evt_type, uint32_t data)
{
    switch (evt_type)
    {
        case IRQ_UART_ERROR:
            
            break;
            
        case IRQ_UART_RX:
            
            p_ble_pickit->uart.receive_in_progress = true;
            p_ble_pickit->uart.rx_buffer[p_ble_pickit->uart.index] = (uint8_t) (data);
            p_ble_pickit->uart.index++;
            break;
            
        case IRQ_UART_TX:
            
            break;
            
    }
}

void ble_init(UART_MODULE uart_id, uint32_t data_rate, ble_pickit_t * _p_ble_pickit, acquisitions_params_t *_p_acquisitions)
{       
    p_ble_pickit = _p_ble_pickit;
    p_acquisitions = _p_acquisitions;
    m_uart_id = uart_id;
    
    uart_init(  uart_id, ble_uart_event_handler, IRQ_UART_RX, data_rate, UART_STD_PARAMS);
    
    m_dma_id = dma_init(    NULL, 
                            DMA_CONT_PRIO_2, 
                            DMA_INT_NONE, 
                            DMA_EVT_START_TRANSFER_ON_IRQ, 
                            uart_get_tx_irq(uart_id), 
                            0xff);   
    
    p_ble_pickit->status.device.reset_type = RESET_BLE_PICKIT;
    p_ble_pickit->flags.reset_requested = 1;
}

void ble_stack_tasks()
{         
    if (m_uart_id != UART_NUMBER_OF_MODULES)
    {
        if (p_ble_pickit->uart.index != p_ble_pickit->uart.old_index)
        {                
            mUpdateTick(p_ble_pickit->uart.tick);                        
            p_ble_pickit->uart.old_index = p_ble_pickit->uart.index;
        }
        else if (p_ble_pickit->uart.index > 0)
        {
            if (mTickCompare(p_ble_pickit->uart.tick) >= TICK_300US)
            {
                if (	(p_ble_pickit->uart.index == 3) && \
                        (p_ble_pickit->uart.rx_buffer[0] == 'A') && \
                        (p_ble_pickit->uart.rx_buffer[1] == 'C') && \
                        (p_ble_pickit->uart.rx_buffer[2] == 'K'))
                {
                    p_ble_pickit->uart.message_type = UART_ACK_MESSAGE;
                }
                else if (	(p_ble_pickit->uart.index == 3) && \
                            (p_ble_pickit->uart.rx_buffer[0] == 'N') && \
                            (p_ble_pickit->uart.rx_buffer[1] == 'A') && \
                            (p_ble_pickit->uart.rx_buffer[2] == 'K'))
                {
                    p_ble_pickit->uart.message_type = UART_NAK_MESSAGE;
                }
                else if (p_ble_pickit->uart.index >= 5)
                {
                    p_ble_pickit->uart.message_type = UART_NEW_MESSAGE;
                }
                else
                {
                    p_ble_pickit->uart.message_type = UART_NO_MESSAGE;
                }

                p_ble_pickit->uart.index = 0;
                p_ble_pickit->uart.receive_in_progress = false;
                p_ble_pickit->uart.old_index = p_ble_pickit->uart.index;
            }
        }

        if (p_ble_pickit->uart.message_type == UART_NEW_MESSAGE)
        {
            uint16_t crc_calc, crc_uart;

            p_ble_pickit->uart.message_type = UART_NO_MESSAGE;

            crc_calc = fu_crc_16_ibm(p_ble_pickit->uart.rx_buffer, p_ble_pickit->uart.rx_buffer[1] + 2);
            crc_uart = (p_ble_pickit->uart.rx_buffer[p_ble_pickit->uart.rx_buffer[1] + 2] << 8) + (p_ble_pickit->uart.rx_buffer[p_ble_pickit->uart.rx_buffer[1] + 3] << 0);

            if (crc_calc == crc_uart)
            {                
                dma_tx.src_start_addr = (void *) __ack;
                dma_tx.dst_start_addr = (void *) uart_get_tx_reg(m_uart_id);
                dma_tx.src_size = 3;
                dma_tx.dst_size = 1;
                dma_tx.cell_size = 1;

                dma_set_transfer_params(m_dma_id, &dma_tx);  
                dma_channel_enable(m_dma_id, ON, false);     // Do not take care of the 'force_transfer' boolean value because the DMA channel is configure to execute a transfer on event when Tx is ready (IRQ source is Tx of a peripheral - see notes of dma_set_transfer_params()).
            }   
            else
            {
                p_ble_pickit->uart.rx_buffer[0] = ID_NONE;
                
                dma_tx.src_start_addr = (void *) __nak;
                dma_tx.dst_start_addr = (void *) uart_get_tx_reg(m_uart_id);
                dma_tx.src_size = 3;
                dma_tx.dst_size = 1;
                dma_tx.cell_size = 1;

                dma_set_transfer_params(m_dma_id, &dma_tx);  
                dma_channel_enable(m_dma_id, ON, false);     // Do not take care of the 'force_transfer' boolean value because the DMA channel is configure to execute a transfer on event when Tx is ready (IRQ source is Tx of a peripheral - see notes of dma_set_transfer_params()).}            
            }

            switch (p_ble_pickit->uart.rx_buffer[0])
            {
                case ID_BOOT_MODE:
                    if ((p_ble_pickit->uart.rx_buffer[1] == 2) && (p_ble_pickit->uart.rx_buffer[2] == 0xb0) && (p_ble_pickit->uart.rx_buffer[3] == 0x07))
                    {
                        if (!p_ble_pickit->flags.reset_requested)
                        {
                            __boot_sequence();
                        }
                    }                
                    break;
                    
                case ID_NAME:
                    memcpy(p_ble_pickit->status.device.name, &p_ble_pickit->uart.rx_buffer[2], p_ble_pickit->uart.rx_buffer[1]);
                    p_ble_pickit->status.device.name[p_ble_pickit->uart.rx_buffer[1]] = '\0';
                    p_ble_pickit->status.device.reset_type = RESET_BLE_PICKIT;
                    p_ble_pickit->flags.reset_requested = 1;
                    break;

                case ID_SOFTWARE_VERSION:
                    memcpy(p_ble_pickit->status.device.software_version, &p_ble_pickit->uart.rx_buffer[2], p_ble_pickit->uart.rx_buffer[1]);
                    p_ble_pickit->status.device.software_version[p_ble_pickit->uart.rx_buffer[1]] = '\0';
                    break;

                case ID_PA_LNA:
                    if ((p_ble_pickit->uart.rx_buffer[2]) != p_ble_pickit->status.hardware.pa_lna_enable)
                    {
                        p_ble_pickit->status.hardware.pa_lna_enable = p_ble_pickit->uart.rx_buffer[2];
                        p_ble_pickit->status.device.reset_type = RESET_BLE_PICKIT;
                        p_ble_pickit->flags.reset_requested = 1;
                    }
                    break;

                case ID_HARDWARE_STATUS:
                    p_ble_pickit->status.hardware.is_hardware_status_updated = true;
                    p_ble_pickit->status.hardware.pa_lna_enable = GET_BIT(p_ble_pickit->uart.rx_buffer[2], 0);
                    p_ble_pickit->status.hardware.led_enable = GET_BIT(p_ble_pickit->uart.rx_buffer[2], 1);
                    break;

                case ID_BLE_CONNECTION_STATUS:                
                    p_ble_pickit->status.connection.is_connection_status_updated = true;
                    p_ble_pickit->status.connection.is_in_advertising_mode = GET_BIT(p_ble_pickit->uart.rx_buffer[2], 0);
                    p_ble_pickit->status.connection.is_connected_to_a_central = GET_BIT(p_ble_pickit->uart.rx_buffer[2], 1);
                    p_ble_pickit->status.device.security_connection.is_lock = GET_BIT(p_ble_pickit->uart.rx_buffer[2], 7);
                    break;

                case ID_BLE_PARAMETERS_STATUS:     
                    p_ble_pickit->status.current_params.is_gap_params_updated = true;
                    p_ble_pickit->status.current_params.conn_params.min_conn_interval = (p_ble_pickit->uart.rx_buffer[2] << 8) | (p_ble_pickit->uart.rx_buffer[3] << 0);
                    p_ble_pickit->status.current_params.conn_params.max_conn_interval = (p_ble_pickit->uart.rx_buffer[4] << 8) | (p_ble_pickit->uart.rx_buffer[5] << 0);
                    p_ble_pickit->status.current_params.conn_params.slave_latency = (p_ble_pickit->uart.rx_buffer[6] << 8) | (p_ble_pickit->uart.rx_buffer[7] << 0);
                    p_ble_pickit->status.current_params.conn_params.conn_sup_timeout = (p_ble_pickit->uart.rx_buffer[8] << 8) | (p_ble_pickit->uart.rx_buffer[9] << 0);
                    p_ble_pickit->status.current_params.phy = p_ble_pickit->uart.rx_buffer[10];
                    p_ble_pickit->status.current_params.att_mtu = p_ble_pickit->uart.rx_buffer[11];                   
                    p_ble_pickit->status.current_params.data_length = p_ble_pickit->uart.rx_buffer[12];
                    p_ble_pickit->status.current_params.conn_evt_len_ext = p_ble_pickit->uart.rx_buffer[13];
                    break;

                case ID_BLE_CHARACTERISTICS_PROPERTIES:
                    p_ble_pickit->status.characteristics.is_characteristics_status_updated = true;
                    p_ble_pickit->status.characteristics._0x1501.properties.b = (p_ble_pickit->uart.rx_buffer[2] & 0x7f);
                    p_ble_pickit->status.characteristics._0x1501.is_notify_enabled = GET_BIT(p_ble_pickit->uart.rx_buffer[2], 7);
                    p_ble_pickit->status.characteristics._0x1503.properties.b = (p_ble_pickit->uart.rx_buffer[3] & 0x7f);
                    p_ble_pickit->status.characteristics._0x1503.is_notify_enabled = GET_BIT(p_ble_pickit->uart.rx_buffer[3], 7);
                    break;
                    
                case ID_BLE_CONN_PARAMS:
                    // No need to reset. "sd_ble_gap_conn_param_update(..)" is already executed in BLE_PICKIT.
                    p_ble_pickit->status.preferred_params.conn_params.min_conn_interval = (p_ble_pickit->uart.rx_buffer[2] << 8) | (p_ble_pickit->uart.rx_buffer[3] << 0);
                    p_ble_pickit->status.preferred_params.conn_params.max_conn_interval = (p_ble_pickit->uart.rx_buffer[4] << 8) | (p_ble_pickit->uart.rx_buffer[5] << 0);
                    p_ble_pickit->status.preferred_params.conn_params.slave_latency = (p_ble_pickit->uart.rx_buffer[6] << 8) | (p_ble_pickit->uart.rx_buffer[7] << 0);
                    p_ble_pickit->status.preferred_params.conn_params.conn_sup_timeout = (p_ble_pickit->uart.rx_buffer[8] << 8) | (p_ble_pickit->uart.rx_buffer[9] << 0);
                    break;
                    
                case ID_BLE_PHY_PARAM:
                    // No need to reset. "sd_ble_gap_conn_param_update(..)" is already executed in BLE_PICKIT.
                    p_ble_pickit->status.preferred_params.phy = p_ble_pickit->uart.rx_buffer[2];
                    break;
                    
                case ID_BLE_ATT_MTU_PARAM:
                    // Reset is needed to update this parameter (during boot sequence).
                    p_ble_pickit->status.preferred_params.att_mtu = p_ble_pickit->uart.rx_buffer[2];                    
                    p_ble_pickit->status.device.reset_type = RESET_BLE_PICKIT;
                    p_ble_pickit->flags.reset_requested = 1;
                    break;
                    
                case ID_BLE_DATA_LENGTH_PARAM:
                    // No need to reset. "sd_ble_gap_conn_param_update(..)" is already executed in BLE_PICKIT.
                    p_ble_pickit->status.preferred_params.data_length = p_ble_pickit->uart.rx_buffer[2];
                    break;
                    
                case ID_BLE_CONN_EVT_LENGTH_EXT_PARAM:
                    // Reset is needed to update this parameter (during boot sequence).
                    p_ble_pickit->status.preferred_params.conn_evt_len_ext = p_ble_pickit->uart.rx_buffer[2];                    
                    p_ble_pickit->status.device.reset_type = RESET_BLE_PICKIT;
                    p_ble_pickit->flags.reset_requested = 1;
                    break;
                    
                case ID_CHAR_SPC_STATUS:
                    p_ble_pickit->app_spc.time_x20ms = (p_acquisitions != NULL) ? p_ble_pickit->uart.rx_buffer[2] : 0;
                    p_ble_pickit->flags.notif_app_spc = (p_acquisitions != NULL) ? 1 : 0;
                    mUpdateTick(p_ble_pickit->app_spc.tick);
                    break;
                    
                case ID_CHAR_BUFFER:
                    memcpy(p_ble_pickit->app_buffer.in_data, &p_ble_pickit->uart.rx_buffer[2], p_ble_pickit->uart.rx_buffer[1]);
                    p_ble_pickit->app_buffer.in_length = p_ble_pickit->uart.rx_buffer[1];
                    p_ble_pickit->app_buffer.in_is_updated = true;
                    break;

                case ID_SOFTWARE_RESET:
                    if ((p_ble_pickit->uart.rx_buffer[1] == 1))
                    {
                        p_ble_pickit->status.device.reset_type = (p_ble_pickit->uart.rx_buffer[1] & 3);
                        if (p_ble_pickit->status.device.reset_type == RESET_PIC32_HOST)
                        {
                            p_ble_pickit->flags.software_reset = true;
                        }
                        else
                        {
                            p_ble_pickit->flags.reset_requested = true;
                        }
                    }
                    break;

                default:
                    break;

            }
                            
            memset(p_ble_pickit->uart.rx_buffer, 0, sizeof(p_ble_pickit->uart.rx_buffer));
        }

        if (p_ble_pickit->flags.w > 0)
        {
            if (p_ble_pickit->flags.software_reset)
            {
                if (uart_transmission_has_completed(m_uart_id))
                {
                    software_reset();
                }
            }
            else if (p_ble_pickit->flags.reset_requested)
            {
                if (!vsd_outgoing_message_uart(_reset_request))
                {
                    if (p_ble_pickit->status.device.reset_type == RESET_BOTH)
                    {
                        software_reset();
                    }
                    else
                    {
                        p_ble_pickit->flags.reset_requested = 0;
                    }
                }
            }
            else if (p_ble_pickit->flags.security_mode)
            {
                if (!vsd_outgoing_message_uart(_security_mode))
                {
                    p_ble_pickit->flags.security_mode = 0;
                }
            }
            else if (p_ble_pickit->flags.name)
            {
                if (!vsd_outgoing_message_uart(_name))
                {
                    p_ble_pickit->flags.name = 0;
                }
            }
            else if (p_ble_pickit->flags.software_version)
            {
                if (!vsd_outgoing_message_uart(_software_version))
                {
                    p_ble_pickit->flags.software_version = 0;
                }
            }
            else if (p_ble_pickit->flags.pa_lna)
            {
                if (!vsd_outgoing_message_uart(_pa_lna))
                {
                    p_ble_pickit->flags.pa_lna = 0;
                }
            }
            else if (p_ble_pickit->flags.led_status)
            {
                if (!vsd_outgoing_message_uart(_led_status))
                {
                    p_ble_pickit->flags.led_status = 0;
                }
            }
            else if (p_ble_pickit->flags.adv_interval)
            {
                if (!vsd_outgoing_message_uart(_adv_interval))
                {
                    p_ble_pickit->flags.adv_interval = 0;
                }
            }
            else if (p_ble_pickit->flags.adv_timeout)
            {
                if (!vsd_outgoing_message_uart(_adv_timeout))
                {
                    p_ble_pickit->flags.adv_timeout = 0;
                }
            }               
            else if (p_ble_pickit->flags.ble_pref_conn_params)
            {
                if (!vsd_outgoing_message_uart(_conn_params))
                {
                    p_ble_pickit->flags.ble_pref_conn_params = 0;
                }
            }
            else if (p_ble_pickit->flags.ble_pref_phy_param)
            {
                if (!vsd_outgoing_message_uart(_phy_param))
                {
                    p_ble_pickit->flags.ble_pref_phy_param = 0;
                }
            }
            else if (p_ble_pickit->flags.ble_pref_att_mtu_param)
            {
                if (!vsd_outgoing_message_uart(_att_mtu_param))
                {
                    p_ble_pickit->flags.ble_pref_att_mtu_param = 0;
                }
            }
            else if (p_ble_pickit->flags.ble_pref_data_length_param)
            {
                if (!vsd_outgoing_message_uart(_data_length_param))
                {
                    p_ble_pickit->flags.ble_pref_data_length_param = 0;
                }
            }
            else if (p_ble_pickit->flags.ble_pref_conn_evt_length_ext_param)
            {
                if (!vsd_outgoing_message_uart(_conn_evt_length_ext_param))
                {
                    p_ble_pickit->flags.ble_pref_conn_evt_length_ext_param = 0;
                }
            }
            else if (p_ble_pickit->flags.notif_app_buffer)
            {
                if (p_ble_pickit->status.characteristics._0x1501.is_notify_enabled)
                {                
                    if (!vsd_outgoing_message_uart(_app_buffer))
                    {
                        p_ble_pickit->flags.notif_app_buffer = 0;
                    }
                }
            }
            else if (p_ble_pickit->flags.notif_app_spc)
            {            
                if (!vsd_outgoing_message_uart(_app_spc))
                {
                    p_ble_pickit->flags.notif_app_spc = 0;
                }
            }
        }
        
        if (p_ble_pickit->app_spc.time_x20ms > 0)
        {
            if (mTickCompare(p_ble_pickit->app_spc.tick) >= (p_ble_pickit->app_spc.time_x20ms * TICK_20MS))
            {
                mUpdateTick(p_ble_pickit->app_spc.tick);
                p_ble_pickit->flags.notif_app_spc = 1;
            }
        }
    }
}

static void _security_mode(uint8_t *buffer)
{
	buffer[0] = ID_SECURITY_MODE;
	buffer[1] = 1;
    buffer[2] = p_ble_pickit->status.device.security_connection.enable;
}

static void _name(uint8_t *buffer)
{
    uint8_t i = 0;
    
	buffer[0] = ID_NAME;
	for (i = 0 ; i < 16 ; i++)
    {
        if (p_ble_pickit->status.device.name[i] == '\0')
        {
            break;
        }
        buffer[2+i] = p_ble_pickit->status.device.name[i];
    }
    buffer[1] = i;
}

static void _software_version(uint8_t *buffer)
{
	buffer[0] = ID_SOFTWARE_VERSION;
	buffer[1] = 1;
    buffer[2] = 0x00;
}

static void _pa_lna(uint8_t *buffer)
{
	buffer[0] = ID_PA_LNA;	
    buffer[1] = 1;
    buffer[2] = p_ble_pickit->status.hardware.pa_lna_enable;
}

static void _led_status(uint8_t *buffer)
{
	buffer[0] = ID_LED_STATUS;
    buffer[1] = 1;
    buffer[2] = p_ble_pickit->status.hardware.led_enable;
}

static void _adv_interval(uint8_t *buffer)
{
	buffer[0] = ID_BLE_ADV_INTERVAL;	
	buffer[1] = 2;
    buffer[2] = (p_ble_pickit->status.preferred_params.adv_interval >> 8) & 0xff;
    buffer[3] = (p_ble_pickit->status.preferred_params.adv_interval >> 0) & 0xff;
}

static void _adv_timeout(uint8_t *buffer)
{
	buffer[0] = ID_BLE_ADV_TIMEOUT;	
	buffer[1] = 2;
    buffer[2] = (p_ble_pickit->status.preferred_params.adv_timeout >> 8) & 0xff;
    buffer[3] = (p_ble_pickit->status.preferred_params.adv_timeout >> 0) & 0xff;
}

static void _conn_params(uint8_t *buffer)
{
	buffer[0] = ID_BLE_CONN_PARAMS;
    buffer[1] = 8;
    buffer[2] = (p_ble_pickit->status.preferred_params.conn_params.min_conn_interval >> 8) & 0xff;
    buffer[3] = (p_ble_pickit->status.preferred_params.conn_params.min_conn_interval >> 0) & 0xff;
    buffer[4] = (p_ble_pickit->status.preferred_params.conn_params.max_conn_interval >> 8) & 0xff;
    buffer[5] = (p_ble_pickit->status.preferred_params.conn_params.max_conn_interval >> 0) & 0xff;
    buffer[6] = (p_ble_pickit->status.preferred_params.conn_params.slave_latency >> 8) & 0xff;
    buffer[7] = (p_ble_pickit->status.preferred_params.conn_params.slave_latency >> 0) & 0xff;
    buffer[8] = (p_ble_pickit->status.preferred_params.conn_params.conn_sup_timeout >> 8) & 0xff;
    buffer[9] = (p_ble_pickit->status.preferred_params.conn_params.conn_sup_timeout >> 0) & 0xff;
}

static void _phy_param(uint8_t *buffer)
{
	buffer[0] = ID_BLE_PHY_PARAM;
    buffer[1] = 1;
    buffer[2] = p_ble_pickit->status.preferred_params.phy;
}

static void _att_mtu_param(uint8_t *buffer)
{
	buffer[0] = ID_BLE_ATT_MTU_PARAM;
    buffer[1] = 1;
    buffer[2] = p_ble_pickit->status.preferred_params.att_mtu;
}

static void _data_length_param(uint8_t *buffer)
{
	buffer[0] = ID_BLE_DATA_LENGTH_PARAM;
    buffer[1] = 1;
    buffer[2] = p_ble_pickit->status.preferred_params.data_length;
}

static void _conn_evt_length_ext_param(uint8_t *buffer)
{
	buffer[0] = ID_BLE_CONN_EVT_LENGTH_EXT_PARAM;
    buffer[1] = 1;
    buffer[2] = p_ble_pickit->status.preferred_params.conn_evt_len_ext;
}

static void _reset_request(uint8_t *buffer)
{
	buffer[0] = ID_SOFTWARE_RESET;
	buffer[1] = 1;
	buffer[2] = p_ble_pickit->status.device.reset_type;
}

static void _app_buffer(uint8_t *buffer)
{
	buffer[0] = ID_CHAR_BUFFER;
	buffer[1] = p_ble_pickit->app_buffer.out_length;
    memcpy(&buffer[2], p_ble_pickit->app_buffer.out_data, p_ble_pickit->app_buffer.out_length);
}

static void _app_spc(uint8_t *buffer)
{
    uint16_t _temperature = fu_get_integer_value(p_acquisitions->ntc.temperature * 10.0);
    uint8_t _voltage = fu_get_integer_value(p_acquisitions->voltage.average * 10.0);
    uint8_t _current = fu_get_integer_value(p_acquisitions->current.average * 1000.0);    
    
	buffer[0] = ID_CHAR_SPC_STATUS;
	buffer[1] = 7;
    buffer[2] = p_ble_pickit->app_spc.time_x20ms;
    buffer[3] = _temperature >> 0;
    buffer[4] = _temperature >> 8;
    buffer[5] = _voltage;
    buffer[6] = _current;
    buffer[7] = p_acquisitions->speed >> 0;
    buffer[8] = p_acquisitions->speed >> 8;
}

static uint8_t vsd_outgoing_message_uart(p_ble_function ptr)
{
    static state_machine_t sm;
	static uint8_t buffer[256] = {0};
    uint16_t crc = 0;

	switch (sm.index)
	{

        case 0:
            sm.index++;
            sm.tick = mGetTick();            
			/* no break */
        case 1:
            
            if (uart_transmission_has_completed(m_uart_id) && !p_ble_pickit->uart.receive_in_progress)
            {
                memset(buffer, 0, sizeof(buffer));
                sm.index++;
                sm.tick = mGetTick();
            }
            break;
            
        case 2:
            if (mTickCompare(sm.tick) >= TICK_400US)
        	{
        		if (uart_transmission_has_completed(m_uart_id) && !p_ble_pickit->uart.receive_in_progress)
				{
					sm.index++;
					(*ptr)(buffer);
                    crc = fu_crc_16_ibm(buffer, buffer[1]+2);
                    buffer[buffer[1]+2] = (crc >> 8) & 0xff;
                    buffer[buffer[1]+3] = (crc >> 0) & 0xff;
				}
        		else
        		{
        			sm.index = 1;
        		}
        	}
            break;
            
		case 3:

            dma_tx.src_start_addr = (void *)buffer;
            dma_tx.dst_start_addr = (void *)uart_get_tx_reg(m_uart_id);
            dma_tx.src_size = buffer[1] + 4;
            dma_tx.dst_size = 1;
            dma_tx.cell_size = 1;
            
            dma_set_transfer_params(m_dma_id, &dma_tx);  
            dma_channel_enable(m_dma_id, ON, false);     // Do not take care of the 'force_transfer' boolean value because the DMA channel is configure to execute a transfer on event when Tx is ready (IRQ source is Tx of a peripheral - see notes of dma_set_transfer_params()).
			
            sm.index++;
			sm.tick = mGetTick();
			break;

		case 4:
        
            if (uart_transmission_has_completed(m_uart_id))
            {
                sm.index++;
                sm.tick = mGetTick();
            }
			break;

		case 5:

            if (p_ble_pickit->uart.message_type == UART_ACK_MESSAGE)
            {
                p_ble_pickit->uart.message_type = UART_NO_MESSAGE;
                sm.index = 0;
            }
            else if (p_ble_pickit->uart.message_type == UART_NAK_MESSAGE)
            {
                p_ble_pickit->uart.message_type = UART_NO_MESSAGE;
                sm.index = 3;
            }
            else if (mTickCompare(sm.tick) >= TICK_10MS)
            {
                sm.index = 3;
            }
			break;

		default:
            sm.index = 0;
			break;

	}

	return sm.index;
}
 