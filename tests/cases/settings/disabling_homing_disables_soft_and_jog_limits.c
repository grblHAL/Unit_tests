#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    settings.homing.flags.enabled = true;
    settings.limits.soft_enabled.mask = AXES_BITMASK;
    settings.limits.flags.jog_soft_limited = true;
    CHECK(store_setting(Setting_HomingEnable, "0") == Status_OK);
    CHECK(!settings.homing.flags.enabled);
    CHECK(settings.limits.soft_enabled.mask == 0);
    CHECK(!settings.limits.flags.jog_soft_limited);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
