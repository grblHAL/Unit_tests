#include "support/soft_limit_motion_host.h"
int main(void)
{
    prepare_soft_limit_motion();
    request_outside_soft_limits();
    CHECK(!soft_hold_seen && wake_calls == 0);
    CHECK(plan_get_current_block() == NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    return EXIT_SUCCESS;
}
