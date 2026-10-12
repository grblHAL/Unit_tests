#include "support/secondary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_secondary_pwm_settings(false);
    CHECK(secondary_pwm_store(Setting_RpmMax1, "12345") == Status_OK);
    CHECK(secondary_pwm_store(Setting_RpmMin1, "250") == Status_OK);
    CHECK(secondary_pwm_changes == 2 && primary_pwm_changes == 0);
    secondary_pwm_settings->cfg.rpm_max = 1;
    secondary_pwm_settings->cfg.rpm_min = 0;
    secondary_pwm_owner->load();
    NEAR(secondary_pwm_settings->cfg.rpm_max, 12345);
    NEAR(secondary_pwm_settings->cfg.rpm_min, 250);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
