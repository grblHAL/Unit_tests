#include "support/system_plugin_host.h"
#include "check.h"

int main(void)
{
    prepare_system_plugin();
    CHECK(system_command("$PING=abc") == Status_InvalidStatement);
    CHECK(plugin_calls == 0);
    return EXIT_SUCCESS;
}
