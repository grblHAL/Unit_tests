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
    /* Queue a plugin-supplied message through the public motion API. Parser
       comment ownership is tested separately, including its known leak. */
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 100;
    data.message = malloc(sizeof("Future move"));
    CHECK(data.message != NULL);
    strcpy(data.message, "Future move");
    float target[N_AXIS] = {60};
    CHECK(mc_line(target, &data) == Status_Handled);
    CHECK(data.message == NULL); /* Planner accepted ownership. */
    CHECK(message_calls == 0);
    stop_program();
    engine_execute_tasks(STATE_IDLE);
    CHECK(message_calls == 0);
    CHECK(strstr(engine_output, "Future move") == NULL);
    CHECK(axis_pulses[X_AXIS] < 1600);
    return EXIT_SUCCESS;
}
