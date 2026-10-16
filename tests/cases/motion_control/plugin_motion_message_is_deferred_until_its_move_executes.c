#include "support/motion_message_host.h"
int main(void)
{
    prepare_motion_messages();
    queue_message_move(1, "Cut starts");
    CHECK(motion_message_calls == 0);
    execute_motion_program();
    CHECK(motion_message_calls == 1 && strcmp(motion_messages[0], "Cut starts") == 0);
    CHECK(motion_message_positions[0] >= 0 && motion_message_positions[0] < 80);
    CHECK(physical_position[X_AXIS] == 80);
    engine_execute_tasks(STATE_IDLE);
    CHECK(motion_message_calls == 1);
    CHECK(engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
