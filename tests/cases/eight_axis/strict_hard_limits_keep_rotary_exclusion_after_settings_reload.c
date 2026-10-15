#include "support/rotary_limit_settings_host.h"
int main(void)
{
    prepare_rotary_limit_settings();
    CHECK(store_setting(Setting_HardLimitsEnable, "7") == Status_OK);
    settings.limits.flags.hard_disabled_rotary = false;
    sys.hard_limits.mask = 255;
    settings_init();
    CHECK(settings.limits.flags.check_at_init && settings.limits.flags.hard_disabled_rotary);
    CHECK(settings.steppers.is_rotary.mask == 40 && sys.hard_limits.mask == 215);
    const setting_detail_t *detail = setting_get_details(Setting_HardLimitsEnable, NULL);
    CHECK(detail && setting_get_int_value(detail, 0) == 7);
    return EXIT_SUCCESS;
}
