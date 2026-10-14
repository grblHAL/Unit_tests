#include "support/homing_command_host.h"
int main(void)
{
    prepare_homing_command();
    homing_command_controls.e_stop = true;
    CHECK(execute_homing_command("$H") == Status_EStop);
    check_no_command_homing_motion();
    return EXIT_SUCCESS;
}
