#include "support/system_plugin_host.h"
#include "check.h"

int main(void)
{
    prepare_system_plugin();
    sys.blocking_event = true;
    CHECK(system_command("$ECHO=abc") == Status_NotAllowedCriticalEvent);
    CHECK(plugin_calls == 0);
    return EXIT_SUCCESS;
}
