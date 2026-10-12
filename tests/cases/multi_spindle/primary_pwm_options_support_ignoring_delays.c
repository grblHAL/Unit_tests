#include "support/primary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_primary_pwm_settings(true);
    CHECK(store_setting(Setting_SpindlePWMOptions, "31") == Status_OK);
    CHECK(!settings.pwm_spindle.flags.pwm_disable);
    CHECK(settings.pwm_spindle.flags.ignore_delays);
    CHECK(change_callbacks == 1);
    const setting_detail_t *detail = setting_get_details(Setting_SpindlePWMOptions, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 31);
    return EXIT_SUCCESS;
}
