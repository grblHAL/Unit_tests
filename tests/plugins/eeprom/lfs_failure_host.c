#include "lfs_failure_host.h"
#include "nvs_buffer.h"
unsigned lfs_reads, lfs_writes;
static nvs_transfer_result_t read_failed(uint8_t *buffer, uint32_t address, uint32_t size, bool checksum)
{ CHECK(buffer && address == 4096 && size == 8 && !checksum); lfs_reads++; return false; }
static nvs_transfer_result_t write_failed(uint32_t address, uint8_t *buffer, uint32_t size, bool checksum)
{ CHECK(buffer && address == 4096 && size == 256 && !checksum); lfs_writes++; return false; }
nvs_io_t *nvs_buffer_get_physical(void)
{
 static nvs_io_t nvs = {.type = NVS_EEPROM, .size = 4096, .size_max = 16384, .memcpy_from_nvs = read_failed, .memcpy_to_nvs = write_failed};
 return &nvs;
}
