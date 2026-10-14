#include "support/homing_command_host.h"
int main(void)
{
    prepare_homing_command();
    settings.homing.flags.enabled = false;
    CHECK(execute_homing_command("$H") == Status_HomingDisabled);
    check_no_command_homing_motion();
    return EXIT_SUCCESS;
}
