#include "support/secondary_pwm_settings_host.h"
int main(void)
{
    secondary_pwm_no_change_callback = true;
    prepare_secondary_pwm_settings(false);
    CHECK(grbl.on_settings_changed == primary_pwm_changed);
    CHECK(secondary_pwm_store(Setting_PWMFreq1, "1234") == Status_OK);
    CHECK(secondary_pwm_changes == 0);
    NEAR(secondary_pwm_settings->cfg.pwm_freq, 1234);
    const setting_detail_t *detail = setting_get_details(Setting_PWMFreq1, NULL);
    CHECK(detail != NULL);
    NEAR(setting_get_float_value(detail, 0), 1234);
    secondary_pwm_owner->load();
    NEAR(secondary_pwm_settings->cfg.pwm_freq, 1234);
    unsigned before = primary_pwm_changes;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){.spindle = true});
    CHECK(primary_pwm_changes == before + 1 && secondary_pwm_changes == 0);
    CHECK(grbl.on_settings_changed == primary_pwm_changed);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
