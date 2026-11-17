#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$O") == Status_OK);
    CHECK(sys.flags.optional_stop_enable && changed_controls.stop_enable);
    CHECK(system_command("$O") == Status_OK);
    CHECK(!sys.flags.optional_stop_enable && control_change_calls == 2);
    return EXIT_SUCCESS;
}
