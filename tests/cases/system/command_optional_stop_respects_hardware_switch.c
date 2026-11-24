#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    hal.signals_cap.stop_enable = true;
    CHECK(system_command("$O") == Status_InvalidStatement);
    CHECK(!sys.flags.optional_stop_enable && control_change_calls == 0);
    return EXIT_SUCCESS;
}
