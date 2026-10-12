#include "support/homing_host.h"
#include "check.h"

int main(void)
{
    prepare_homing();
    settings.homing.flags.manual = true;
    settings.homing.cycle[0].mask = 0;
    limits_set_homing_axes();
    sys.position[X_AXIS] = 123;
    sys.position[Y_AXIS] = 456;
    CHECK(mc_homing_cycle((axes_signals_t){.mask = Y_AXIS_BIT}) == Status_OK);
    CHECK(sys.homed.mask == Y_AXIS_BIT);
    CHECK(sys.position[Y_AXIS] == 0);
    CHECK(sys.position[X_AXIS] == 123);
    CHECK(wake_calls == 0);
    CHECK(limit_enable_calls == 0);
    CHECK(completed_calls == 1 && homing_success);
    return EXIT_SUCCESS;
}
