#include "support/settings_initialized_host.h"
int main(void)
{
    prepare_initialized_settings(2.0f);
    settings.version.build = 250102;
    settings.flags.settings_downgrade = false;
    settings.safety_door.coolant_on_delay = 1.25f;
    settings.coolant.on_delay = 50;
    settings.pwm_spindle.at_speed_tolerance = 4.5f;
    settings.spindle.at_speed_tolerance = 1.0f;
    settings.arc_tolerance = 0.025f;
    settings_write_global();
    settings_init();
    CHECK(settings.version.build == GRBL_BUILD - 20000000UL);
    CHECK(settings.coolant.on_delay == 1250);
    NEAR(settings.spindle.at_speed_tolerance, 4.5f);
    NEAR(settings.arc_tolerance, 0.025f);
    unsigned migration_callbacks = change_callbacks;
    CHECK(migration_callbacks >= 2);
    settings.safety_door.coolant_on_delay = 9.0f;
    settings.pwm_spindle.at_speed_tolerance = 9.0f;
    settings_init();
    CHECK(settings.coolant.on_delay == 1250);
    NEAR(settings.spindle.at_speed_tolerance, 4.5f);
    CHECK(change_callbacks == migration_callbacks + 1);
    return EXIT_SUCCESS;
}
