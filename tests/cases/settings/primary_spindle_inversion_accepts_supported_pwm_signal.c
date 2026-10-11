#include "support/primary_pwm_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_primary_pwm_settings(true);
    CHECK(store_setting(Setting_SpindleInvertMask, "7") == Status_OK);
    CHECK(settings.pwm_spindle.invert.on && settings.pwm_spindle.invert.ccw && settings.pwm_spindle.invert.pwm);
    CHECK(change_callbacks == 1);
    const setting_detail_t *detail = setting_get_details(Setting_SpindleInvertMask, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 7);
    return EXIT_SUCCESS;
}
