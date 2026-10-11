#include "support/primary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_primary_pwm_settings(true);
    CHECK(store_setting(Setting_SpindlePWMOptions, "15") == Status_OK);
    CHECK(!settings.pwm_spindle.flags.pwm_disable);
    CHECK(settings.pwm_spindle.flags.enable_rpm_controlled);
    CHECK(settings.pwm_spindle.flags.laser_mode_disable);
    CHECK(settings.pwm_spindle.flags.pwm_ramped);
    CHECK(change_callbacks == 1);
    const setting_detail_t *detail = setting_get_details(Setting_SpindlePWMOptions, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 15);
    return EXIT_SUCCESS;
}
