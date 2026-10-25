#include <stdio.h>
#include <string.h>
#include "eeprom.h"
#include "grbl_eeprom_extensions.h"
#include "grbl/crc.h"
#include "check.h"
int main(void)
{
 remove("checksum-read.dat"); set_eeprom_name("checksum-read.dat");
 uint8_t data[] = {3, 7, 19, 255}, result[8] = {0};
 uint16_t checksum = calc_checksum(data, sizeof(data));
 CHECK(memcpy_to_eeprom(64, data, sizeof(data), false));
 eeprom_put_char(68, (uint8_t)checksum);
#if NVS_CRC_BYTES > 1
 eeprom_put_char(69, (uint8_t)(checksum >> 8));
#endif
 /* A larger caller buffer keeps the regression observable without an overread. */
 bool valid = memcpy_from_eeprom(result, 64, sizeof(data), true);
 eeprom_close(); CHECK(remove("checksum-read.dat") == 0);
 CHECK(memcmp(data, result, sizeof(data)) == 0); CHECK(valid); return 0;
}
