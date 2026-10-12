#include "support/secondary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    hal.nvs.type = NVS_EEPROM;
    CHECK(spindle1_settings_add(true) == NULL);
    CHECK(hal.nvs.driver_area.address == 0);
    return EXIT_SUCCESS;
}
