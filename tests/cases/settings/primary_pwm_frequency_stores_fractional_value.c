#include "support/primary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_primary_pwm_settings(true);
    CHECK(store_setting(Setting_PWMFreq, "1234.5") == Status_OK);
    NEAR(settings.pwm_spindle.pwm_freq, 1234.5f);
    CHECK(change_callbacks == 1);
    const setting_detail_t *detail = setting_get_details(Setting_PWMFreq, NULL);
    CHECK(detail != NULL);
    NEAR(setting_get_float_value(detail, 0), 1234.5f);
    return EXIT_SUCCESS;
}
