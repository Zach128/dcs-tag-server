#ifndef DCS_PAYLOAD_H__
#define DCS_PAYLOAD_H__

#include "ble_srv_common.h"

#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))

static uint8_t cic_payload[11] = {0x66, 0x77, 0x64, 0x73, 0x2c, 0x73, 0x6d, 0x75, 0x2c, 0x73, 0x6d};
static uint8_t iac_payload[2] = {0x12, 0x34};

static void set_attr_value(ble_gatts_attr_t * attr_char_value, uint8_t *value, uint8_t *size);

#endif
