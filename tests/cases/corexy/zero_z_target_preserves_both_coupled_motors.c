#include "support/corexy_limits_host.h"

int main(void)
{
    prepare_corexy_limits();
    kinematics.limits_set_target_pos(Z_AXIS);
    CHECK(sys.position[X_AXIS] == 1040 && sys.position[Y_AXIS] == 560);
    CHECK(sys.position[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
