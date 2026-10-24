#include <stdio.h>
#include "eeprom.h"
#include "check.h"
int main(void)
{
 remove("unused.dat"); set_eeprom_name("unused.dat"); eeprom_close(); eeprom_close();
 FILE *file = fopen("unused.dat", "rb"); CHECK(file == NULL);
 CHECK(eeprom_get_char(10) == 255); eeprom_put_char(10, 21); eeprom_close();
 file = fopen("unused.dat", "rb"); CHECK(file);
 CHECK(fseek(file, 10, SEEK_SET) == 0); CHECK(fgetc(file) == 21);
 CHECK(fclose(file) == 0); CHECK(remove("unused.dat") == 0);
 return 0;
}
