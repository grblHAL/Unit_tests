#include <stdio.h>
#include <string.h>
#include "eeprom.h"
#include "grbl_eeprom_extensions.h"
#include "check.h"
int main(void)
{
 remove("block.dat"); set_eeprom_name("block.dat");
 uint8_t data[] = {3, 7, 19, 255}, result[6] = {0};
 eeprom_put_char(63, 12); eeprom_put_char(68, 13);
 CHECK(memcpy_to_eeprom(64, data, sizeof(data), false));
 CHECK(memcpy_from_eeprom(result, 64, sizeof(data), false)); CHECK(memcmp(data, result, sizeof(data)) == 0);
 CHECK(eeprom_get_char(63) == 12 && eeprom_get_char(68) == 13);
 CHECK(memcpy_to_eeprom(64, data, 0, false));
 CHECK(memcpy_from_eeprom(result, 64, 0, false)); CHECK(eeprom_get_char(64) == 3);
 eeprom_close(); CHECK(remove("block.dat") == 0); return 0;
}
