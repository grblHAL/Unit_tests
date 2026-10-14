#include "support/sleep_wait_host.h"
int main(void)
{
    start_sleep_cut();
    hold_motion();
    unsigned pulses = axis_pulses[X_AXIS];
    wait_for_sleep();
    CHECK(sleep_wait_calls == 1);
    CHECK(sys.rt_exec_state & EXEC_SLEEP);
    CHECK(axis_pulses[X_AXIS] == pulses);
    CHECK(plan_get_current_block() != NULL);
    return EXIT_SUCCESS;
}
