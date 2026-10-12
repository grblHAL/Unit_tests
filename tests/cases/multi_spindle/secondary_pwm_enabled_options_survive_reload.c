#include "support/secondary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_secondary_pwm_settings(false);
    CHECK(secondary_pwm_store(Setting_SpindlePWMOptions1, "31") == Status_OK);
    secondary_pwm_settings->cfg.flags.value = 0;
    secondary_pwm_owner->load();
    CHECK(!secondary_pwm_settings->cfg.flags.pwm_disable);
    CHECK(secondary_pwm_settings->cfg.flags.enable_rpm_controlled);
    CHECK(secondary_pwm_settings->cfg.flags.laser_mode_disable);
    CHECK(secondary_pwm_settings->cfg.flags.pwm_ramped);
    CHECK(secondary_pwm_settings->cfg.flags.ignore_delays);
    CHECK(strcmp(setting_get_value(setting_get_details(Setting_SpindlePWMOptions1, NULL), 0), "31") == 0);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
