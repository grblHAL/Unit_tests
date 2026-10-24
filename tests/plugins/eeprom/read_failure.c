#include "eeprom_host.h"
int main(void)
{
 prepare_eeprom(); CHECK(i2c_eeprom_init());
 uint8_t result[8]; memset(result, 99, sizeof(result)); fail_transfer = 1;
 bool ok = hal.nvs.memcpy_from_nvs(result, 10, sizeof(result), false);
 CHECK(transfers == 1); CHECK(result[0] == 99); CHECK(!ok);
 return 0;
}
