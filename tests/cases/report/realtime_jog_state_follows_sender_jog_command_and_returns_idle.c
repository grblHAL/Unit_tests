#include "support/jog_motion_host.h"
int main(void)
{
    prepare_jog_motion();
    CHECK(system_command("$J=G91X1F100") == Status_OK);
    CHECK(state_get() == STATE_JOG);
    engine_output[0] = '\0'; realtime_report();
    CHECK(strncmp(engine_output, "<Jog|", 5) == 0);
    finish_jog_motion();
    CHECK(physical_position[X_AXIS] == 80 && axis_pulses[X_AXIS] == 80);
    engine_output[0] = '\0'; realtime_report();
    CHECK(strncmp(engine_output, "<Idle|", 6) == 0);
    return EXIT_SUCCESS;
}
