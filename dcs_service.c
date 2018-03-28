
#include <stdint.h>
#include <string.h>
#include "nrf_gpio.h"
#include "dcs_service.h"
#include "dcs_payload.h"
#include "ble_srv_common.h"
#include "app_error.h"
#include "SEGGER_RTT.h"

// ALREADY_DONE_FOR_YOU: Declaration of a function that will take care of some housekeeping of ble connections related to our service and characteristic
void ble_dcs_service_on_ble_evt(ble_os_t * p_dcs_service, ble_evt_t * p_ble_evt)
{
	
	uint32_t err_code;
	
    // OUR_JOB: Step 3.D Implement switch case handling BLE events related to our service. 
		switch (p_ble_evt->header.evt_id)
		{
				case BLE_GAP_EVT_CONNECTED:
						p_dcs_service->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
						break;
				case BLE_GAP_EVT_DISCONNECTED:
						p_dcs_service->conn_handle = BLE_CONN_HANDLE_INVALID;
						break;
				
				case BLE_EVT_USER_MEM_REQUEST:
						/*
						err_code = sd_ble_user_mem_reply(p_dcs_service->conn_handle, &m_dhc_mem_block);
						if (err_code != NRF_SUCCESS) {
							printf("ERROR sd_ble_user_mem_reply: %u\r\n", (unsigned int)err_code);
						} else {
							printf("USER_MEM_REQUEST OK\r\n");
						} */
						
						break;

        case BLE_EVT_USER_MEM_RELEASE:
						printf("USER_MEM_RELEASE\r\n");
						break;
				
				default:
						// No implementation needed.
						break;
		}
}

/**@brief Function for adding our new characterstic to "Our service" that we initiated in the previous tutorial. 
 *
 * @param[in]   p_dcs_service        Our Service structure.
 *
 */
static uint32_t cic_char_add(ble_os_t * p_dcs_service)
{
    // OUR_JOB: Step 2.A, Add the custom characteristic UUID
		uint32_t            err_code;
		ble_uuid_t          char_uuid;
		ble_uuid128_t       base_uuid = BLE_UUID_OUR_BASE_UUID;
		char_uuid.uuid      = BLE_UUID_CIC_CHARACTERISTC_UUID;
		err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
		APP_ERROR_CHECK(err_code);
	
    // OUR_JOB: Step 2.F Add read/write properties to our characteristic
    ble_gatts_char_md_t char_md;
    memset(&char_md, 0, sizeof(char_md));
		char_md.char_props.read = 1;
		char_md.char_props.write = 1;
    
    // OUR_JOB: Step 3.A, Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
   
    
    // OUR_JOB: Step 2.B, Configure the attribute metadata
    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md));  
    attr_md.vloc        = BLE_GATTS_VLOC_STACK;
    attr_md.vlen				= 1;
		
    // OUR_JOB: Step 2.G, Set read/write security levels to our characteristic
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    
    // OUR_JOB: Step 2.C, Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
    attr_char_value.p_uuid      = &char_uuid;
		attr_char_value.p_attr_md   = &attr_md;
		
    // OUR_JOB: Step 2.H, Set characteristic length in number of bytes
		attr_char_value.max_len     = 16;
		attr_char_value.init_len    = 11;
		uint8_t value[11]           = {0x66, 0x77, 0x64, 0x73, 0x2c, 0x73, 0x6d, 0x75, 0x2c, 0x73, 0x6d};
		attr_char_value.p_value     = value;

    // OUR_JOB: Step 2.E, Add our new characteristic to the service
		err_code = sd_ble_gatts_characteristic_add(p_dcs_service->service_handle,
                                   &char_md,
                                   &attr_char_value,
                                   &p_dcs_service->char_handles);
		APP_ERROR_CHECK(err_code);

    return NRF_SUCCESS;
}

/**@brief Function for adding our new characterstic to "Our service" that we initiated in the previous tutorial. 
 *
 * @param[in]   p_dcs_service        Our Service structure.
 *
 */
static uint32_t iac_char_add(ble_os_t * p_dcs_service)
{
    // OUR_JOB: Step 2.A, Add a custom characteristic UUID
    uint32_t            err_code;
		ble_uuid_t          char_uuid;
		ble_uuid128_t       base_uuid = BLE_UUID_OUR_BASE_UUID;
		char_uuid.uuid      = BLE_UUID_IAC_CHARACTERISTC_UUID;
		err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
		APP_ERROR_CHECK(err_code);
	
    // OUR_JOB: Step 2.F Add read/write properties to our characteristic
    ble_gatts_char_md_t char_md;
    memset(&char_md, 0, sizeof(char_md));
		char_md.char_props.read = 1;
		char_md.char_props.write = 1;
    
    // OUR_JOB: Step 3.A, Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
   
    
    // OUR_JOB: Step 2.B, Configure the attribute metadata
    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md));  
    attr_md.vloc        = BLE_GATTS_VLOC_STACK;
    attr_md.vlen				= 1;
		
    // OUR_JOB: Step 2.G, Set read/write security levels to our characteristic
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
		BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    
    // OUR_JOB: Step 2.C, Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
    attr_char_value.p_uuid      = &char_uuid;
		attr_char_value.p_attr_md   = &attr_md;
		
    // OUR_JOB: Step 2.H, Set characteristic length in number of bytes
		attr_char_value.max_len     = 16;
		attr_char_value.init_len    = 4;
		uint8_t value[4]            = {0x87,0x65,0x43,0x21};
		attr_char_value.p_value     = value;
		
    // OUR_JOB: Step 2.E, Add our new characteristic to the service
		err_code = sd_ble_gatts_characteristic_add(p_dcs_service->service_handle,
                                   &char_md,
                                   &attr_char_value,
                                   &p_dcs_service->char_handles);
		APP_ERROR_CHECK(err_code);

    return NRF_SUCCESS;
}

/**@brief Function for initiating our new service.
 *
 * @param[in]   p_dcs_service        Our Service structure.
 *
 */
void dcs_service_init(ble_os_t * p_dcs_service)
{
    uint32_t   err_code; // Variable to hold return codes from library and softdevice functions

    // FROM_SERVICE_TUTORIAL: Declare 16-bit service and 128-bit base UUIDs and add them to the BLE stack
    ble_uuid_t        service_uuid;
    ble_uuid128_t     base_uuid = BLE_UUID_OUR_BASE_UUID;
    service_uuid.uuid = BLE_UUID_DCS_SERVICE_UUID;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &service_uuid.type);
    APP_ERROR_CHECK(err_code);    
    
    // OUR_JOB: Step 3.B, Set our service connection handle to default value. I.e. an invalid handle since we are not yet in a connection.
		p_dcs_service->conn_handle = BLE_CONN_HANDLE_INVALID;
		
    // FROM_SERVICE_TUTORIAL: Add our service
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid,
                                        &p_dcs_service->service_handle);
    
    APP_ERROR_CHECK(err_code);
    
    // OUR_JOB: Call the function xxx_char_add() to add our new characteristics to the service. 
    cic_char_add(p_dcs_service);
		iac_char_add(p_dcs_service);
}

// ALREADY_DONE_FOR_YOU: Function to be called when updating characteristic value
void dcs_cic_update(ble_os_t *p_dcs_service, const uint8_t * p_data)
{
    // OUR_JOB: Step 3.E, Update characteristic value
		if (p_dcs_service->conn_handle != BLE_CONN_HANDLE_INVALID)
		{
			uint16_t               len = sizeof(*p_data) / sizeof(uint16_t);
			ble_gatts_hvx_params_t hvx_params;
			memset(&hvx_params, 0, sizeof(hvx_params));

			hvx_params.handle = p_dcs_service->char_handles.value_handle;
			hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
			hvx_params.offset = 0;
			hvx_params.p_len  = &len;
			hvx_params.p_data = (uint8_t*)p_data;  

			sd_ble_gatts_hvx(p_dcs_service->conn_handle, &hvx_params);
		}
		
}
