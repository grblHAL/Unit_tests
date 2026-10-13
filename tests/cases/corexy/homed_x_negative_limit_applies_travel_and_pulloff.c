#include "support/corexy_limits_host.h"

int main(void)
{
    prepare_corexy_limits();
    settings.homing.flags.force_set_origin = false;
    settings.homing.dir_mask.value = 1;
    kinematics.limits_set_machine_positions((axes_signals_t){.mask = X_AXIS_BIT});
    CHECK(sys.position[X_AXIS] == -15680);
    CHECK(sys.position[Y_AXIS] == -16160);
    CHECK(sys.position[Z_AXIS] == -160);
    return EXIT_SUCCESS;
}
