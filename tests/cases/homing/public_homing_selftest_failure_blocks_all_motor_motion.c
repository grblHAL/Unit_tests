#include "support/homing_command_host.h"
int main(void)
{
    prepare_homing_command();
    sys.alarm = Alarm_SelftestFailed;
    CHECK(execute_homing_command("$H") == Status_SelfTestFailed);
    check_no_command_homing_motion();
    return EXIT_SUCCESS;
}
