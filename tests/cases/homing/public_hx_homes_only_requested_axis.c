#include "support/homing_command_host.h"
int main(void)
{
    prepare_homing_command();
    CHECK(execute_homing_command("$HX") == Status_OK);
    CHECK(homing_success && completed_calls == 1);
    CHECK(sys.homed.mask == (1u << 0));
    CHECK(physical_position[0] == switch_position[0] - 10);
    CHECK(axis_pulses[0] > 0);
    for(unsigned i = 0; i < N_AXIS; i++) if(i != 0) CHECK(axis_pulses[i] == 0);
    CHECK(state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
