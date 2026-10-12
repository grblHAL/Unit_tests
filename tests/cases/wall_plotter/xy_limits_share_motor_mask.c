#include "support/wall_host.h"
#include "check.h"

int main(void)
{
    prepare_wall();
    CHECK(kinematics.limits_get_axis_mask(X_AXIS) == 3);
    CHECK(kinematics.limits_get_axis_mask(Y_AXIS) == 3);
    CHECK(kinematics.limits_get_axis_mask(Z_AXIS) == 4);
    return EXIT_SUCCESS;
}
