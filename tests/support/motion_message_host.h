#pragma once
#include "support/motion_program_host.h"
static unsigned motion_message_calls;
static char motion_messages[4][64];
static int32_t motion_message_positions[4];
static status_code_t route_motion_message(char *message)
{
    CHECK(state_get() == STATE_CYCLE && motion_message_calls < 4);
    CHECK(strlen(message) < sizeof(motion_messages[0]));
    strcpy(motion_messages[motion_message_calls], message);
    motion_message_positions[motion_message_calls++] = physical_position[X_AXIS];
    *message = '\0'; /* A plugin consumes the message for its own user interface. */
    return Status_OK;
}
static inline void prepare_motion_messages(void)
{
    prepare_motion_program();
    grbl.on_gcode_message = route_motion_message;
}
static inline void queue_message_move(float x, const char *message)
{
    plan_line_data_t data;
    plan_data_init(&data);
    data.feed_rate = 100;
    data.message = malloc(strlen(message) + 1);
    CHECK(data.message != NULL);
    strcpy(data.message, message);
    float target[N_AXIS] = {x};
    CHECK(mc_line(target, &data) == Status_Handled);
    CHECK(data.message == NULL);
}
