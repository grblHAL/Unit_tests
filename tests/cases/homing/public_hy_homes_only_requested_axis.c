#include "support/homing_command_host.h"
int main(void)
{
    prepare_homing_command();
    CHECK(execute_homing_command("$HY") == Status_OK);
    CHECK(homing_success && completed_calls == 1);
    CHECK(sys.homed.mask == (1u << 1));
    CHECK(physical_position[1] == switch_position[1] - 10);
    CHECK(axis_pulses[1] > 0);
    for(unsigned i = 0; i < N_AXIS; i++) if(i != 1) CHECK(axis_pulses[i] == 0);
    CHECK(state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
