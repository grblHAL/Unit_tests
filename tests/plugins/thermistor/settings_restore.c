#include "therm_host.h"
int main(void)
{
    therm_start(true);
    therm_float(457, 5100);
    therm_float(458, 5);
    therm_float(459, 50);
    adc = 1551;
    CHECK(therm_command("THRMTEMP", STATE_IDLE, NULL) == Status_OK && strstr(output, "30.0 degC"));
    unsigned before = saves;
    registered_settings->restore();
    CHECK(saves == before + 1 && claims == 1);
    const setting_detail_t *settings = registered_settings->settings;
    CHECK(settings[0].id == 455 && settings[1].id == 456 && settings[2].id == 457 &&
          settings[3].id == 458 && settings[4].id == 459);
    CHECK(((setting_get_float_ptr)settings[0].get_value)(455) == -1 &&
          *(uint8_t *)settings[1].value == 0 && *(float *)settings[2].value == 0 &&
          *(float *)settings[3].value == 0 && *(float *)settings[4].value == 0);
    adc = 3102;
    CHECK(therm_command("THRMTEMP", STATE_IDLE, NULL) == Status_OK && strstr(output, "25.0 degC"));
    for (unsigned i = 0; i < 6; i++)
        therm_report(false);
    CHECK(stops == 0 && claims == 1 && warnings == 0);
    return 0;
}
