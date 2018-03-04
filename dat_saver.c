#include "fds.h"
#include "fstorage.h"
#include "dat_saver.h"
#include "SEGGER_RTT.h"

static void my_fds_evt_handler(fds_evt_t const * const p_fds_evt)
{
    switch (p_fds_evt->id)
    {
        case FDS_EVT_INIT:
            if (p_fds_evt->result != FDS_SUCCESS)
            {
                // Initialization failed.
								SEGGER_RTT_WriteString(0, "Failed to initialise File Data Storage module");
            }
            break;
				case FDS_EVT_WRITE:
						SEGGER_RTT_WriteString(0, "Writing...\r\n");
						if (p_fds_evt->result == FDS_SUCCESS)
						{
							write_flag=1;
						}
						break;
        default:
            break;
    }
}

ret_code_t fds_dcs_init (void)
{
	
		ret_code_t ret = fds_register(my_fds_evt_handler);
		if (ret != FDS_SUCCESS)
		{
					return ret;
					SEGGER_RTT_WriteString(0, "Failed to register FDS module");
		}
		ret = fds_init();
		if (ret != FDS_SUCCESS)
		{
				return ret;
		}
		
		return NRF_SUCCESS;
		
}

ret_code_t fds_dcs_overwrite(uint32_t const * const data, uint16_t length, uint16_t rec_key)
{
		#define FILE_ID     0x1111
		#define REC_KEY     0x2222
		//static uint32_t const m_deadbeef[2] = {0xDEADBEEF,0xBAADF00D};
		fds_record_t        record;
		fds_record_desc_t   record_desc;
		fds_record_chunk_t  record_chunk;
		// Set up data.
		record_chunk.p_data         = data;
		record_chunk.length_words   = length;
		
		// Set up record.
		record.file_id              = FDS_DCS_ATT_FILE_ID;
		record.key              		= rec_key;
		record.data.p_chunks       = &record_chunk;
		record.data.num_chunks   = 1;
		
		SEGGER_RTT_printf(0, "About to write %s to record 0x%4x", data, rec_key);
		
		ret_code_t ret = fds_record_write(&record_desc, &record);
		if (ret != FDS_SUCCESS)
		{
				SEGGER_RTT_WriteString(0, "Write failed\r\n");
				return ret;
		}
		//NRF_LOG_PRINTF("Writing Record ID = %d \r\n",record_desc.record_id);
		return NRF_SUCCESS;
}

ret_code_t fds_dcs_read(uint16_t rec_key, char * p_data)
{
		#define FILE_ID     0x1111
		#define REC_KEY     0x2222
		fds_flash_record_t  flash_record;
		fds_record_desc_t   record_desc;
		fds_find_token_t    ftok ={0};//Important, make sure you zero init the ftok token
		uint32_t err_code;
		
		// Loop until all records with the given key and file ID have been found.
		while (fds_record_find(FDS_DCS_ATT_FILE_ID, rec_key, &record_desc, &ftok) == FDS_SUCCESS)
		{
				err_code = fds_record_open(&record_desc, &flash_record);
				if ( err_code != FDS_SUCCESS)
				{
					SEGGER_RTT_printf(0, "ERROR: Failed to open record. Err code %d\r\n", err_code);
					return err_code;		
				}
				
				SEGGER_RTT_printf(0, "Found Record ID = %d\r\n", record_desc.record_id);
				//NRF_LOG_PRINTF("Data = ");
				p_data = (char *) flash_record.p_data;
				for (uint8_t i=0;i<flash_record.p_header->tl.length_words;i++)
				{
					SEGGER_RTT_printf(0, "0x%8x\r\n",p_data[i]);
				}
				SEGGER_RTT_WriteString(0, "\r\n");
				// Access the record through the flash_record structure.
				// Close the record when done.
				err_code = fds_record_close(&record_desc);
				if (err_code != FDS_SUCCESS)
				{
					return err_code;	
				}
		}
		return NRF_SUCCESS;
		
}
