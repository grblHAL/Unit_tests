#include "eeprom_host.h"
#include "grbl/crc.h"
int main(void)
{
 prepare_eeprom(); CHECK(i2c_eeprom_init());
 CHECK(hal.nvs.type == (EEPROM_IS_FRAM ? NVS_FRAM : NVS_EEPROM));
 uint8_t data[300], result[300];
 for(unsigned i = 0; i < sizeof(data); i++) data[i] = (uint8_t)(i * 3 + 7);
 unsigned address = page_size() - 3;
 CHECK(hal.nvs.memcpy_to_nvs(address, data, sizeof(data), true));
 CHECK(memcmp(memory + address, data, sizeof(data)) == 0);
 CHECK(memory[address - 1] == 255 && memory[address + sizeof(data) + NVS_CRC_BYTES] == 255);
 unsigned write_calls = transfers;
 CHECK(transactions[0].count == 3 && !transactions[0].read);
 CHECK(hal.nvs.memcpy_from_nvs(result, address, sizeof(result), true));
 CHECK(memcmp(result, data, sizeof(data)) == 0);
 CHECK(transactions[write_calls].read && transactions[write_calls].count == 255);
 CHECK(transactions[write_calls + 1].count == 45);
 memory[address + 17] ^= 1;
 CHECK(!hal.nvs.memcpy_from_nvs(result, address, sizeof(result), true));
#if EEPROM_IS_FRAM
 CHECK(delays == 0);
#else
 CHECK(delays > 0);
#endif
 return 0;
}
