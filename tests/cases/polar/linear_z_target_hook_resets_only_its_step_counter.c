#include "support/polar_segment_host.h"
int main(void)
{
    prepare_polar_segments();
    sys.position[X_AXIS] = 100; sys.position[Y_AXIS] = 200; sys.position[Z_AXIS] = 300;
    kinematics.limits_set_target_pos(Z_AXIS);
    CHECK(sys.position[X_AXIS] == 100 && sys.position[Y_AXIS] == 200 && sys.position[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
