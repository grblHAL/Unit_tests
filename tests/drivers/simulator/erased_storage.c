#include <stdio.h>
#include "eeprom.h"
#include "check.h"
int main(void)
{
 remove("erased.dat"); set_eeprom_name("erased.dat");
 for(uint32_t address = 0; address < 4096; address++) CHECK(eeprom_get_char(address) == 0xFF);
 eeprom_put_char(0, 0x12); eeprom_put_char(4095, 0x34); eeprom_put_char(123, 0x56);
 CHECK(eeprom_get_char(0) == 0x12 && eeprom_get_char(4095) == 0x34);
 CHECK(eeprom_get_char(123) == 0x56 && eeprom_get_char(124) == 0xFF);
 eeprom_close();
 FILE *file = fopen("erased.dat", "rb"); CHECK(file);
 CHECK(fseek(file, 0, SEEK_END) == 0); CHECK(ftell(file) == 4096);
 rewind(file); CHECK(fgetc(file) == 0x12); CHECK(fclose(file) == 0);
 eeprom_close(); CHECK(remove("erased.dat") == 0);
 return 0;
}
