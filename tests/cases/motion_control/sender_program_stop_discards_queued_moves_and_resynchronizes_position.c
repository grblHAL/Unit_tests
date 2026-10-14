#include "support/stop_motion_host.h"
int main(void)
{
    start_stop_motion();
    unsigned before = axis_pulses[X_AXIS];
    stop_program();
    CHECK(axis_pulses[X_AXIS] >= before && axis_pulses[X_AXIS] < 1600);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(stop_timer_calls > 0);
    return EXIT_SUCCESS;
}
