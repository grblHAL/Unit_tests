#include <stdio.h>
#include "eeprom.h"
#include "check.h"
int main(void)
{
 FILE *file = fopen("existing.dat", "wb"); CHECK(file);
 for(unsigned i = 0; i < 4096; i++) CHECK(fputc(i & 255, file) != EOF);
 CHECK(fclose(file) == 0); set_eeprom_name("existing.dat");
 CHECK(eeprom_get_char(0) == 0 && eeprom_get_char(255) == 255 && eeprom_get_char(4095) == 255);
 eeprom_put_char(255, 42); CHECK(eeprom_get_char(254) == 254 && eeprom_get_char(255) == 42);
 eeprom_close();
 file = fopen("existing.dat", "rb"); CHECK(file);
 CHECK(fseek(file, 255, SEEK_SET) == 0); CHECK(fgetc(file) == 42); CHECK(fgetc(file) == 0);
 CHECK(fclose(file) == 0); CHECK(remove("existing.dat") == 0);
 return 0;
}
