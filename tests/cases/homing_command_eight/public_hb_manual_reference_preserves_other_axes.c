#include "support/homing_command_host.h"
int main(void)
{
    prepare_manual_homing_command();
    CHECK(execute_homing_command("$HB") == Status_OK);
    check_manual_command_axis(4);
    return EXIT_SUCCESS;
}
