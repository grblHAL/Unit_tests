#include "support/primary_pwm_settings_host.h"

int main(void)
{
    prepare_primary_pwm_settings(true);
    settings.pwm_spindle.flags.enable_rpm_controlled = false;
    settings.pwm_spindle.flags.laser_mode_disable = true;
    settings.pwm_spindle.flags.pwm_ramped = true;
    CHECK(store_setting(Setting_SpindlePWMBehaviour, "1") == Status_OK);
    CHECK(settings.pwm_spindle.flags.enable_rpm_controlled);
    CHECK(store_setting(Setting_SpindlePWMBehaviour, "0") == Status_OK);
    CHECK(!settings.pwm_spindle.flags.enable_rpm_controlled);
    CHECK(settings.pwm_spindle.flags.laser_mode_disable);
    CHECK(settings.pwm_spindle.flags.pwm_ramped);
    return EXIT_SUCCESS;
}
