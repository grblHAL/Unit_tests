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
    sys.position[Z_AXIS] = -160;
    kinematics.limits_set_target_pos(X_AXIS);
    CHECK(sys.position[X_AXIS] == 240);
    CHECK(sys.position[Y_AXIS] == -240);
    CHECK(sys.position[Z_AXIS] == -160);
    return EXIT_SUCCESS;
}
