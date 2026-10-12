#include "support/primary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_primary_pwm_settings(true);
    CHECK(store_setting(Setting_SpindlePWMOptions, "15") == Status_OK);
    CHECK(store_setting(Setting_SpindlePWMOptions, "0") == Status_OK);
    CHECK(settings.pwm_spindle.flags.pwm_disable);
    CHECK(!settings.pwm_spindle.flags.enable_rpm_controlled);
    CHECK(!settings.pwm_spindle.flags.laser_mode_disable);
    CHECK(!settings.pwm_spindle.flags.pwm_ramped);
    CHECK(!settings.pwm_spindle.flags.ignore_delays);
    CHECK(change_callbacks == 2);
    return EXIT_SUCCESS;
}
