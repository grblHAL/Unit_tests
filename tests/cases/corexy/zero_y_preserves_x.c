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
    sys.position[X_AXIS] = 1040;
    sys.position[Y_AXIS] = 560;
    kinematics.limits_set_target_pos(Y_AXIS);
    CHECK(sys.position[X_AXIS] == 800);
    CHECK(sys.position[Y_AXIS] == 800);
    return EXIT_SUCCESS;
}
