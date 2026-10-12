#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store(); settings.homing.flags.enabled = false;
    CHECK(store_setting(Setting_SoftLimitsEnable, "1") == Status_SoftLimitError);
    CHECK(settings.limits.soft_enabled.mask == 0); CHECK(sys.soft_limits.mask == 0);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
