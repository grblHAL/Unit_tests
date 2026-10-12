#include "support/system_plugin_host.h"
#include "check.h"

int main(void)
{
    prepare_system_plugin();
    grbl.on_unknown_sys_command = plugin_unknown;
    CHECK(system_command("$mystery=Mixed case") == Status_OK);
    CHECK(unknown_calls == 1 && strcmp(unknown_line, "MYSTERY=Mixed case") == 0);
    return EXIT_SUCCESS;
}
