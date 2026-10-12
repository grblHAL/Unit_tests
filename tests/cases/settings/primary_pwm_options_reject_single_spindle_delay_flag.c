#include "support/primary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_primary_pwm_settings(true);
    CHECK(store_setting(Setting_SpindlePWMOptions, "15") == Status_OK);
    CHECK(store_setting(Setting_SpindlePWMOptions, "17") == Status_SettingValueOutOfRange);
    CHECK(settings.pwm_spindle.flags.enable_rpm_controlled);
    CHECK(settings.pwm_spindle.flags.laser_mode_disable);
    CHECK(settings.pwm_spindle.flags.pwm_ramped);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
