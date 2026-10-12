#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$B") == Status_OK);
    CHECK(sys.flags.block_delete_enabled && changed_controls.block_delete);
    CHECK(system_command("$B") == Status_OK);
    CHECK(!sys.flags.block_delete_enabled && control_change_calls == 2);
    return EXIT_SUCCESS;
}
