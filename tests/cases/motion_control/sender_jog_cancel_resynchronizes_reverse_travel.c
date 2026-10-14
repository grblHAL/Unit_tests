#include "support/jog_cancel_stream_host.h"

int main(void)
{
    jog_direction = -1;
    jog_stream_program = "$J=G21G91X-10F100\n$J=G21G91X-10F100\n";
    run_cancelled_jog(false);
    CHECK(jog_stop_position < 0);
    CHECK(sys.position[X_AXIS] == physical_position[X_AXIS]);
    CHECK(axis_pulses[X_AXIS] == jog_stop_pulses);
    return EXIT_SUCCESS;
}
