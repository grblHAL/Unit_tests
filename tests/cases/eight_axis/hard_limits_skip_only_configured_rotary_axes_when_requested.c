#include "support/rotary_limit_settings_host.h"
int main(void)
{
    prepare_rotary_limit_settings();
    CHECK(store_setting(Setting_HardLimitsEnable, "5") == Status_OK);
    CHECK(settings.limits.flags.hard_enabled && settings.limits.flags.hard_disabled_rotary);
    CHECK(!settings.limits.flags.check_at_init);
    CHECK(sys.hard_limits.mask == 215 && rotary_limit_driver_enabled);
    const setting_detail_t *detail = setting_get_details(Setting_HardLimitsEnable, NULL);
    CHECK(detail && setting_get_int_value(detail, 0) == 5);
    CHECK(rotary_limit_driver_calls == 1 && change_callbacks == 1);
    return EXIT_SUCCESS;
}
