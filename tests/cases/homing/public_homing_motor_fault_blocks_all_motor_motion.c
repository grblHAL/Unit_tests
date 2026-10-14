#include "support/homing_command_host.h"
int main(void)
{
    prepare_homing_command();
    homing_command_controls.motor_fault = true;
    CHECK(execute_homing_command("$H") == Status_MotorFault);
    check_no_command_homing_motion();
    return EXIT_SUCCESS;
}
