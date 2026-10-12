#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store(); settings.homing.flags.enabled = true;
    for(unsigned axis = 0; axis < N_AXIS; axis++) settings.axis[axis].max_travel = -200;
    CHECK(store_setting(Setting_SoftLimitsEnable, "1") == Status_OK);
    CHECK(store_setting(Setting_SoftLimitsEnable, "0") == Status_OK);
    CHECK(settings.limits.soft_enabled.mask == 0); CHECK(sys.soft_limits.mask == 0);
    CHECK(change_callbacks == 2);
    return EXIT_SUCCESS;
}
