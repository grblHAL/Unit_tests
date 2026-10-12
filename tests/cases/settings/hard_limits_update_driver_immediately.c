#include "support/settings_host.h"
#include "check.h"
static unsigned enable_calls;
static bool last_enabled;
static void enable_limits(bool enabled, axes_signals_t homing) { CHECK(homing.mask == 0); last_enabled = enabled; enable_calls++; }
int main(void)
{
    prepare_settings_store();
    hal.limits.enable = enable_limits;
    CHECK(store_setting(Setting_HardLimitsEnable, "1") == Status_OK);
    CHECK(last_enabled && sys.hard_limits.mask == AXES_BITMASK);
    CHECK(store_setting(Setting_HardLimitsEnable, "0") == Status_OK);
    CHECK(!last_enabled && sys.hard_limits.mask == 0);
    CHECK(enable_calls == 2 && change_callbacks == 2);
    return EXIT_SUCCESS;
}
