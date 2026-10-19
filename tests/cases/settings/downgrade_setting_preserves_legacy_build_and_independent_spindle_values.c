#include "support/settings_initialized_host.h"
int main(void)
{
    prepare_initialized_settings(2.0f);
    settings.version.build = 250102;
    settings.flags.settings_downgrade = true;
    settings.safety_door.coolant_on_delay = 1.25f;
    settings.coolant.on_delay = 50;
    settings.pwm_spindle.at_speed_tolerance = 4.5f;
    settings.spindle.at_speed_tolerance = 1.0f;
    settings_write_global();
    settings_init();
    CHECK(settings.version.build == 250102);
    CHECK(settings.coolant.on_delay == 50);
    NEAR(settings.spindle.at_speed_tolerance, 1.0f);
    NEAR(settings.pwm_spindle.at_speed_tolerance, 4.5f);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
