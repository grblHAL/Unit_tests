#include "support/canned_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_spindle();
    execute_canned("G0Z1");
    CHECK(canned_block("M3S1000") == Status_OK);
    axis_pulses[Z_AXIS] = 0;
    canned_spindle_events = 0;
    execute_canned("G98G84Z-1R0P0F100");
    CHECK(axis_pulses[Z_AXIS] == 320);
    CHECK(physical_position[Z_AXIS] == 80);
    CHECK(sys.position[Z_AXIS] == 80);
    CHECK(canned_spindle_events == 3);
    CHECK(canned_spindle_log[1].state.ccw);
    CHECK(canned_spindle_log[1].z == -80);
    CHECK(!canned_spindle_log[2].state.ccw);
    CHECK(canned_spindle_log[2].z == 80);
    return EXIT_SUCCESS;
}
