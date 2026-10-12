#include "support/homing_host.h"
#include "check.h"

int main(void)
{
    prepare_homing();
    settings.homing.flags.manual = true;
    settings.homing.cycle[0].mask = 0;
    limits_set_homing_axes();
    for(unsigned axis = 0; axis < N_AXIS; axis++) sys.position[axis] = 400;
    CHECK(mc_homing_cycle((axes_signals_t){0}) == Status_OK);
    CHECK(sys.homed.mask == AXES_BITMASK);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(sys.position[axis] == 0);
    CHECK(wake_calls == 0);
    CHECK(limit_enable_calls == 0);
    CHECK(completed_calls == 1 && homing_success);
    return EXIT_SUCCESS;
}
