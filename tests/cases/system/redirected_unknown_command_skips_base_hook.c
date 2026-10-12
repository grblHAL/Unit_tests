#include "support/system_plugin_host.h"
#include "check.h"

int main(void)
{
    prepare_system_plugin();
    grbl.on_unknown_sys_command = plugin_unknown;
    CHECK(redirected_command("$MYSTERY=abc") == Status_InvalidStatement);
    CHECK(unknown_calls == 0);
    return EXIT_SUCCESS;
}
