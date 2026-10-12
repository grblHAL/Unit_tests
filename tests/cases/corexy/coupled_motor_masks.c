#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "machine_limits.h"
#include "check.h"
void corexy_init(void);
int main(void)
{
    engine_prepare();
    limits_init();
    corexy_init();
    CHECK(kinematics.limits_get_axis_mask(X_AXIS) == (X_AXIS_BIT | Y_AXIS_BIT));
    CHECK(kinematics.limits_get_axis_mask(Y_AXIS) == (X_AXIS_BIT | Y_AXIS_BIT));
    CHECK(kinematics.limits_get_axis_mask(Z_AXIS) == Z_AXIS_BIT);
    return EXIT_SUCCESS;
}
