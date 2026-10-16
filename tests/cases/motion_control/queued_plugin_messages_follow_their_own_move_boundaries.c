#include "support/motion_message_host.h"
int main(void)
{
    prepare_motion_messages();
    queue_message_move(1, "First cut");
    queue_message_move(2, "Second cut");
    CHECK(motion_message_calls == 0);
    execute_motion_program();
    CHECK(motion_message_calls == 2);
    CHECK(strcmp(motion_messages[0], "First cut") == 0);
    CHECK(strcmp(motion_messages[1], "Second cut") == 0);
    CHECK(motion_message_positions[0] >= 0 && motion_message_positions[0] < 80);
    CHECK(motion_message_positions[1] >= 80 && motion_message_positions[1] < 160);
    CHECK(physical_position[X_AXIS] == 160 && axis_pulses[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
