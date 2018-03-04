#include "dcs_payload.h"

#include <stdint.h>
#include <string.h>
#include "dcs_payload.h"
#include "ble_srv_common.h"

static void set_attr_value(ble_gatts_attr_t * attr_char_value, uint8_t *value, uint8_t *size) {
		
		
    // OUR_JOB: Step 2.H, Set characteristic length in number of bytes
		attr_char_value->init_len    = sizeof(*value) / sizeof(value[0]);
		attr_char_value->max_len     = attr_char_value->init_len;
		attr_char_value->p_value     = value;
	
}
