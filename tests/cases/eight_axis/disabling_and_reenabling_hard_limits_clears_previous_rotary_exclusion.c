#include "support/rotary_limit_settings_host.h"
int main(void)
{
    prepare_rotary_limit_settings();
    CHECK(store_setting(Setting_HardLimitsEnable, "5") == Status_OK);
    CHECK(store_setting(Setting_HardLimitsEnable, "0") == Status_OK);
    CHECK(!settings.limits.flags.hard_disabled_rotary && sys.hard_limits.mask == 0);
    CHECK(!rotary_limit_driver_enabled);
    CHECK(store_setting(Setting_HardLimitsEnable, "1") == Status_OK);
    CHECK(sys.hard_limits.mask == 255 && rotary_limit_driver_enabled);
    CHECK(rotary_limit_driver_calls == 3);
    return EXIT_SUCCESS;
}
