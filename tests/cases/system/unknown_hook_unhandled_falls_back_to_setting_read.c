#include "support/system_plugin_host.h"
#include "check.h"

int main(void)
{
    prepare_system_plugin();
    grbl.on_unknown_sys_command = plugin_unknown;
    unknown_status = Status_Unhandled;
    CHECK(system_command("$100") == Status_OK);
    CHECK(unknown_calls == 1 && strcmp(unknown_line, "100") == 0);
    CHECK(strncmp(engine_output, "$100=80.", 8) == 0);
    return EXIT_SUCCESS;
}
