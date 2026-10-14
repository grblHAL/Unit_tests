#include "support/homing_command_host.h"
int main(void)
{
    prepare_homing_command();
    CHECK(execute_homing_command("$H") == Status_OK);
    CHECK(homing_success && completed_calls == 1);
    CHECK(sys.homed.mask == 7);
    for(unsigned axis = 0;
    axis < 3;
    axis++) {
        CHECK(physical_position[axis] == switch_position[axis] - 10);
    CHECK(axis_pulses[axis] > 0);
    } CHECK(state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
