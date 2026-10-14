#include "support/homing_command_host.h"
int main(void)
{
    prepare_homing_command();
    CHECK(execute_homing_command("$HZ") == Status_OK);
    CHECK(homing_success && completed_calls == 1);
    CHECK(sys.homed.mask == (1u << 2));
    CHECK(physical_position[2] == switch_position[2] - 10);
    CHECK(axis_pulses[2] > 0);
    for(unsigned i = 0; i < N_AXIS; i++) if(i != 2) CHECK(axis_pulses[i] == 0);
    CHECK(state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
