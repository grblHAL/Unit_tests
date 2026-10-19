#include "support/segmented_stop_stream_host.h"
static bool drill_stop_phase(void) { return physical_position[Z_AXIS] >= 40; }
int main(void)
{
    program_stop_in_drill = true;
    program_should_stop = drill_stop_phase;
    run_stopped_program("G91G81X1Z-5R2L20F100\nG1X20\n");
    CHECK(program_stop_position[Z_AXIS] > 0);
    CHECK(program_stop_position[X_AXIS] == 0);
    CHECK(sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
