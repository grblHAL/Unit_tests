#include "support/ganging_host.h"
#include "machine_limits.h"

int main(void)
{
    prepare_ganging();
    settings.homing.flags.force_set_origin = true;
    sys.position[Y_AXIS] = -400; sys.position[3] = -400;
    kinematics.limits_set_machine_positions((axes_signals_t){.mask = Z_AXIS_BIT});
    CHECK(sys.position[Z_AXIS] == 0);
    CHECK(sys.position[Y_AXIS] == -400 && sys.position[3] == -400);
    return EXIT_SUCCESS;
}
