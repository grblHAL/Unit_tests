#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store(); settings.homing.flags.enabled = true;
    for(unsigned axis = 0; axis < N_AXIS; axis++) settings.axis[axis].max_travel = -200;
    settings.axis[Y_AXIS].max_travel = 0;
    CHECK(store_setting(Setting_SoftLimitsEnable, "1") == Status_OK);
    CHECK(settings.limits.soft_enabled.mask == AXES_BITMASK);
    CHECK(sys.soft_limits.mask == (AXES_BITMASK & ~Y_AXIS_BIT));
    return EXIT_SUCCESS;
}
