#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    hal.signals_cap.block_delete = true;
    CHECK(system_command("$B") == Status_InvalidStatement);
    CHECK(!sys.flags.block_delete_enabled && control_change_calls == 0);
    return EXIT_SUCCESS;
}
