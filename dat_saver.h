#ifndef DAT_SAVER_H__
#define DAT_SAVER_H__

#include "fds.h"
#include "fstorage.h"

#define FDS_DCS_ATT_FILE_ID 0x1111
#define FDS_DCS_CIC_REC_KEY 0x1010
#define FDS_DCS_IAC_REC_KEY 0x1011

static volatile uint8_t write_flag = 0;

ret_code_t fds_dcs_init (void);

ret_code_t fds_dcs_overwrite(uint32_t const * const data, uint16_t length, uint16_t rec_key);

ret_code_t fds_dcs_read(uint16_t rec_key, char * p_data);

#endif
