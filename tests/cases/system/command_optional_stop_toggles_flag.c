#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$O") == Status_OK);
    CHECK(sys.flags.optional_stop_disable && changed_controls.stop_disable);
    CHECK(system_command("$O") == Status_OK);
    CHECK(!sys.flags.optional_stop_disable && control_change_calls == 2);
    return EXIT_SUCCESS;
}
