#include <stdio.h>
#include "eeprom.h"
#include "grbl_eeprom_extensions.h"
#include "grbl/crc.h"
#include "check.h"
int main(void)
{
 remove("checksum-write.dat"); set_eeprom_name("checksum-write.dat");
 uint8_t data[] = {3, 7, 19, 255};
 uint16_t checksum = calc_checksum(data, sizeof(data));
 CHECK(memcpy_to_eeprom(64, data, sizeof(data), true));
 unsigned saved = eeprom_get_char(68);
#if NVS_CRC_BYTES > 1
 saved |= (unsigned)eeprom_get_char(69) << 8;
#else
 checksum &= 255;
#endif
 eeprom_close(); CHECK(remove("checksum-write.dat") == 0);
 CHECK(saved == checksum); return 0;
}
