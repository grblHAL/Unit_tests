#include "support/canned_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_canned_motion();
    execute_canned("G82Z-1R0P0.1F100");
    CHECK(sys.position[Z_AXIS] == 0 && axis_pulses[Z_AXIS] == 160);
    CHECK(engine_ticks == 100);
    execute_canned("X1"); /* Subsequent holes inherit the programmed dwell and depth. */
    CHECK(sys.position[Z_AXIS] == 0 && physical_position[Z_AXIS] == 0);
    CHECK(axis_pulses[Z_AXIS] == 320);
    CHECK(physical_position[X_AXIS] == 80 && axis_pulses[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && engine_ticks == 200);
    return EXIT_SUCCESS;
}
