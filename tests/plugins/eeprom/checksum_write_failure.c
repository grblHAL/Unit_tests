#include "eeprom_host.h"
int main(void)
{
 prepare_eeprom(); CHECK(i2c_eeprom_init());
 uint8_t data[8] = {1, 4, 9, 16}; fail_transfer = 1;
 CHECK(!hal.nvs.memcpy_to_nvs(32, data, sizeof(data), true));
 CHECK(transfers == 1); CHECK(delays == 0);
 CHECK(memory[32] == 255 && memory[40] == 255); return 0;
}
