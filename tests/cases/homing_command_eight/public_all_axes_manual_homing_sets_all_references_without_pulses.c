#include "support/homing_command_host.h"
int main(void)
{
    prepare_manual_homing_command();
    CHECK(execute_homing_command("$H") == Status_OK);
    CHECK(sys.homed.mask == AXES_BITMASK);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == 0); CHECK(axis_pulses[axis] == 0);
    }
    CHECK(wake_calls == 0 && completed_calls == 1 && homing_success);
    return EXIT_SUCCESS;
}
