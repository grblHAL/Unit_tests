#include "eeprom_host.h"
int main(void)
{
 prepare_eeprom(); start_ok = false;
 CHECK(!i2c_eeprom_init()); CHECK(starts == 1 && probes == 0 && hal.nvs.get_byte == NULL);
 start_ok = true; probe_ok = false; CHECK(!i2c_eeprom_init()); CHECK(probes == 1 && hal.nvs.get_byte == NULL);
 probe_ok = true; CHECK(i2c_eeprom_init()); CHECK(probes == 2);
 CHECK(hal.nvs.type == NVS_EEPROM); CHECK(hal.nvs.size_max == EEPROM_ENABLE / 8 * 1024);
 hal.nvs.put_byte(300, 42); CHECK(hal.nvs.get_byte(300) == 42); CHECK(memory[299] == 255 && memory[301] == 255);
#if EEPROM_ENABLE == 1024
 hal.nvs.put_byte(65536, 91); CHECK(hal.nvs.get_byte(65536) == 91); CHECK(memory[0] == 255);
#endif
 return 0;
}
