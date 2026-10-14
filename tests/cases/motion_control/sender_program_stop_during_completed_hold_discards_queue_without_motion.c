#include "support/stop_motion_host.h"
int main(void)
{
    start_stop_motion();
    hold_motion();
    unsigned before = axis_pulses[X_AXIS];
    stop_program();
    CHECK(axis_pulses[X_AXIS] == before);
    return EXIT_SUCCESS;
}
