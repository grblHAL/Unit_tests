#include "eeprom_host.h"
int main(void)
{
 prepare_eeprom(); CHECK(i2c_eeprom_init());
 uint8_t data[80], result[80]; for(unsigned i = 0; i < sizeof(data); i++) data[i] = (uint8_t)(i + 11);
 unsigned address = 65536 + page_size() - 3;
 CHECK(hal.nvs.memcpy_to_nvs(address, data, sizeof(data), true));
 CHECK(transactions[0].address == address && transactions[0].count == 3);
 CHECK(memory[address - 65536] == 255);
 CHECK(hal.nvs.memcpy_from_nvs(result, address, sizeof(result), true));
 CHECK(memcmp(data, result, sizeof(data)) == 0 && memory[address - 1] == 255);
 return 0;
}
