#include "support/secondary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_secondary_pwm_settings(false);
    CHECK(secondary_pwm_store(Setting_PWMFreq1, "1234") == Status_OK);
    secondary_pwm_settings->cfg.pwm_freq = 10;
    secondary_pwm_owner->load();
    NEAR(secondary_pwm_settings->cfg.pwm_freq, 1234);
    nvs_buffer_free();
    return EXIT_SUCCESS;
}
