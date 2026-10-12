#include "support/system_plugin_host.h"
#include "check.h"

int main(void)
{
    prepare_system_plugin();
    CHECK(system_command("$ echo =Mixed case") == Status_OK);
    CHECK(plugin_calls == 1 && strcmp(plugin_args, "Mixed case") == 0);
    CHECK(strcmp(engine_output, "reply:Mixed case") == 0);
    return EXIT_SUCCESS;
}
