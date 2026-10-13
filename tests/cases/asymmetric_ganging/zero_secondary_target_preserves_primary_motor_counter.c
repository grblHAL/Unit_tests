#include "support/ganging_host.h"

int main(void)
{
    prepare_ganging();
    sys.position[Y_AXIS] = -400; sys.position[3] = -405;
    kinematics.limits_set_target_pos(3);
    CHECK(sys.position[Y_AXIS] == -400);
    CHECK(sys.position[3] == 0);
    return EXIT_SUCCESS;
}
