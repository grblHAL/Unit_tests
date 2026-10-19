#include "support/settings_initialized_host.h"
int main(void)
{
    prepare_initialized_settings(2.0f);
    settings.version.build = 250102;
    settings.flags.settings_downgrade = false;
    settings.safety_door.coolant_on_delay = 0.75f;
    settings.coolant.on_delay = 0;
    settings.pwm_spindle.at_speed_tolerance = settings.spindle.at_speed_tolerance = 3.0f;
    settings_write_global();
    settings_init();
    CHECK(settings.coolant.on_delay == 750);
    NEAR(settings.spindle.at_speed_tolerance, 3.0f);
    CHECK(settings.version.build == GRBL_BUILD - 20000000UL);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
