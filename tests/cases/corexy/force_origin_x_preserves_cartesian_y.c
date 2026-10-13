#include "support/corexy_limits_host.h"

int main(void)
{
    prepare_corexy_limits();
    settings.homing.flags.force_set_origin = true;
    settings.homing.dir_mask.value = 0;
    kinematics.limits_set_machine_positions((axes_signals_t){.mask = X_AXIS_BIT});
    CHECK(sys.position[X_AXIS] == 240);
    CHECK(sys.position[Y_AXIS] == -240);
    CHECK(sys.position[Z_AXIS] == -160);
    return EXIT_SUCCESS;
}
