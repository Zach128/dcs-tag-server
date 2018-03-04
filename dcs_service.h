
#ifndef DCS_SERVICE_H__
#define DCS_SERVICE_H__

#include <stdint.h>
#include "ble.h"
#include "ble_srv_common.h"

// FROM_SERVICE_TUTORIAL: Defining 16-bit service and 128-bit base UUIDs
#define BLE_UUID_OUR_BASE_UUID              {{0x9E, 0x9E, 0x9B, 0xD4, 0xA4, 0xE6, 0xAC, 0xA7, 0x9C, 0x49, 0xA4, 0xF7, 0xFD, 0xDD, 0x16, 0x11}} // 128-bit base UUID
#define BLE_UUID_DCS_SERVICE_UUID                0xD1C0 // Just a random, but recognizable value

// ALREADY_DONE_FOR_YOU: Defining 16-bit characteristic UUID
#define BLE_UUID_CIC_CHARACTERISTC_UUID          0x1234 // Value for Command Instruction Characteristic
#define BLE_UUID_IAC_CHARACTERISTC_UUID          0x4321 // Value for Command Instruction Characteristic

//DCS constants and properties
#define CIC_VALUE_MAX_LEN 20;
#define IAC_VALUE_MAX_LEN 20;

// This structure contains various status information for our service. 
// The name is based on the naming convention used in Nordics SDKs. 
// 'ble’ indicates that it is a Bluetooth Low Energy relevant structure and 
// ‘os’ is short for Our Service). 
typedef struct
{
    uint16_t                    conn_handle;    /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection).*/
    uint16_t                    service_handle; /**< Handle of Our Service (as provided by the BLE stack). */
    // OUR_JOB: Step 2.D, Add handles for the characteristic attributes to our struct
		ble_gatts_char_handles_t    char_handles;
}ble_os_t;

/**@brief Function for handling BLE Stack events related to our service and characteristic.
 *
 * @details Handles all events from the BLE stack of interest to Our Service.
 *
 * @param[in]   p_dcs_service       Our Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_dcs_service_on_ble_evt(ble_os_t * p_dcs_service, ble_evt_t * p_ble_evt);

/**@brief Function for initializing our new service.
 *
 * @param[in]   p_dcs_service       Pointer to Our Service structure.
 */
void dcs_service_init(ble_os_t * p_dcs_service);

/**@brief Function for updating and sending new characteristic values
 *
 * @details The application calls this function whenever our timer_timeout_handler triggers
 *
 * @param[in]   p_dcs_service                     Our Service structure.
 * @param[in]   characteristic_value     New characteristic value.
 */
void dcs_cic_update(ble_os_t *p_dcs_service, const uint8_t * p_data);

#endif  /* _ dcs_service_H__ */
