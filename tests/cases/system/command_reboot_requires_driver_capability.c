#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    hal.reboot = NULL;
    CHECK(system_command("$REBOOT") == Status_InvalidStatement);
    CHECK(strstr(engine_output, "Rebooting") == NULL);
    return EXIT_SUCCESS;
}
