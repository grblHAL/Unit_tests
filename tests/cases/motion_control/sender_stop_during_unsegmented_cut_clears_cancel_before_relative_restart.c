#include "support/segmented_stop_stream_host.h"
static bool linear_stop_point(void) { return axis_pulses[X_AXIS] >= 40; }
int main(void)
{
    program_stop_in_drill = true; // Ordinary linear move does not fill the planner.
    program_should_stop = linear_stop_point;
    run_stopped_program("G1X20F100\n");
    CHECK(program_stop_sent && !program_full_seen);
    CHECK(program_line_reads == 2); // Initial cut, then the sender's relative restart.
    CHECK(program_stop_position[X_AXIS] >= 40 && program_stop_position[X_AXIS] < 1600);
    CHECK(program_stop_position[Y_AXIS] == 0 && program_stop_position[Z_AXIS] == 0);
    CHECK(axis_pulses[X_AXIS] == (unsigned)physical_position[X_AXIS]);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(!sys.cancel && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
