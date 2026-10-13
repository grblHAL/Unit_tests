#include "support/primary_pwm_settings_host.h"

int main(void)
{
    prepare_primary_pwm_settings(true);
    settings.pwm_spindle.flags.enable_rpm_controlled = true;
    CHECK(store_setting(Setting_SpindlePWMBehaviour, "2") == Status_SettingValueOutOfRange);
    CHECK(settings.pwm_spindle.flags.enable_rpm_controlled);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
