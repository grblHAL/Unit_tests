#include "support/secondary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_secondary_pwm_settings(false);
    CHECK(secondary_pwm_store(Setting_SpindleInvertMask1, "7") == Status_OK);
    secondary_pwm_settings->cfg.invert.value = 0;
    secondary_pwm_owner->load();
    CHECK(secondary_pwm_settings->cfg.invert.on);
    CHECK(secondary_pwm_settings->cfg.invert.ccw);
    CHECK(secondary_pwm_settings->cfg.invert.pwm);
    CHECK(strcmp(setting_get_value(setting_get_details(Setting_SpindleInvertMask1, NULL), 0), "7") == 0);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
