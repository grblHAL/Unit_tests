#include "coolant_host.h"
int main(void)
{
    coolant_inputs = 2;
    coolant_prepare(true);
    CHECK(coolant_port(Setting_LaserCoolantOkPort, 1) == Status_OK);
    CHECK(coolant_port(Setting_LaserCoolantTempPort, 1) == Status_OK);
    coolant_float(Setting_LaserCoolantOnDelay, 2);
    coolant_float(Setting_LaserCoolantOffDelay, 0.1f);
    coolant_settings->save();
    FILE *f = fopen("coolant-eeprom.bin", "wb");
    CHECK(f && fwrite(memory, 1, sizeof(memory), f) == sizeof(memory));
    CHECK(fclose(f) == 0);
    return 0;
}
