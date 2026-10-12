#include "support/system_plugin_host.h"
#include "check.h"

int main(void)
{
    prepare_system_plugin();
    stream_write_ptr original = hal.stream.write;
    CHECK(redirected_command("$ECHO=abc") == Status_OK);
    CHECK(strcmp(redirected_output, "reply:abc") == 0);
    CHECK(engine_output[0] == '\0' && hal.stream.write == original);
    return EXIT_SUCCESS;
}
