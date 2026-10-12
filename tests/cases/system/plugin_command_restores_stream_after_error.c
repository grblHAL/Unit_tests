#include "support/system_plugin_host.h"
#include "check.h"

int main(void)
{
    prepare_system_plugin();
    stream_write_ptr original = hal.stream.write;
    plugin_status = Status_InvalidStatement;
    CHECK(redirected_command("$ECHO=abc") == Status_InvalidStatement);
    CHECK(hal.stream.write == original);
    CHECK(strcmp(redirected_output, "reply:abc") == 0 && engine_output[0] == '\0');
    return EXIT_SUCCESS;
}
