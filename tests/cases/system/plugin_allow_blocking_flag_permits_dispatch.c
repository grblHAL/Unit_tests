#include "support/system_plugin_host.h"
#include "check.h"

int main(void)
{
    prepare_system_plugin();
    sys.blocking_event = true;
    CHECK(system_command("$BLOCKOK") == Status_OK);
    CHECK(plugin_calls == 1);
    return EXIT_SUCCESS;
}
