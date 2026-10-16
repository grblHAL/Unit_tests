#include "support/stop_motion_host.h"
static unsigned message_calls;
static status_code_t observe_message(char *message)
{
    CHECK(message != NULL);
    message_calls++;
    return Status_OK;
}
int main(void)
{
    start_stop_motion();
    grbl.on_gcode_message = observe_message;
    queue_motion_program("G1X60F100(MSG,Future move)");
    CHECK(message_calls == 0);
    stop_program();
    engine_execute_tasks(STATE_IDLE);
    CHECK(message_calls == 0);
    CHECK(strstr(engine_output, "Future move") == NULL);
    CHECK(axis_pulses[X_AXIS] < 1600);
    return EXIT_SUCCESS;
}
