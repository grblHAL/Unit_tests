#include "support/system_plugin_host.h"
#include "check.h"

int main(void)
{
    prepare_system_plugin();
    grbl.on_unknown_sys_command = plugin_unknown;
    CHECK(redirected_command("$11=0.02") == Status_AccessDenied);
    CHECK(unknown_calls == 0);
    NEAR(settings.junction_deviation, 0.01f);
    return EXIT_SUCCESS;
}
