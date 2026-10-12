#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    hal.signals_cap.single_block = true;
    CHECK(system_command("$S") == Status_InvalidStatement);
    CHECK(!sys.flags.single_block && control_change_calls == 0);
    return EXIT_SUCCESS;
}
