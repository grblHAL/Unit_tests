#include "support/delta_host.h"
#include "check.h"

int main(void)
{
    prepare_delta();
    CHECK(kinematics.limits_get_axis_mask(X_AXIS) == 1);
    CHECK(kinematics.limits_get_axis_mask(Y_AXIS) == 2);
    CHECK(kinematics.limits_get_axis_mask(Z_AXIS) == 4);
    return EXIT_SUCCESS;
}
