#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$S") == Status_OK);
    CHECK(sys.flags.single_block && changed_controls.single_block);
    CHECK(system_command("$S") == Status_OK);
    CHECK(!sys.flags.single_block && control_change_calls == 2);
    return EXIT_SUCCESS;
}
