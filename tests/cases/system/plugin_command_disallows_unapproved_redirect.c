#include "support/system_plugin_host.h"
#include "check.h"

int main(void)
{
    prepare_system_plugin();
    CHECK(redirected_command("$PRIVATE") == Status_AccessDenied);
    CHECK(plugin_calls == 0 && redirected_output[0] == '\0');
    return EXIT_SUCCESS;
}
