#include "eeprom_host.h"
int main(void)
{
 prepare_eeprom(); CHECK(i2c_eeprom_init());
 uint8_t data[70]; memset(data, 42, sizeof(data));
 fail_transfer = 2;
 CHECK(!hal.nvs.memcpy_to_nvs(page_size() - 3, data, sizeof(data), false));
 CHECK(transfers == 2 && delays == 1); CHECK(memory[page_size() - 1] == 42 && memory[page_size()] == 255);
 fail_transfer = 0;
 CHECK(hal.nvs.memcpy_to_nvs(512, data, sizeof(data), false));
 CHECK(memcmp(memory + 512, data, sizeof(data)) == 0);
 return 0;
}
