#include "support/homing_command_host.h"
int main(void)
{
    prepare_homing_command();
    state_set(STATE_CHECK_MODE);
    CHECK(execute_homing_command("$HZ") == Status_IdleError);
    check_no_command_homing_motion();
    return EXIT_SUCCESS;
}
