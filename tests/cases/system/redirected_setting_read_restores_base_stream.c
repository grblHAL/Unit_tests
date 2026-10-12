#include "support/system_plugin_host.h"
#include "check.h"

int main(void)
{
    prepare_system_plugin();
    stream_write_ptr original = hal.stream.write;
    CHECK(redirected_command("$100") == Status_OK);
    CHECK(strncmp(redirected_output, "$100=80.", 8) == 0);
    CHECK(engine_output[0] == '\0' && hal.stream.write == original);
    return EXIT_SUCCESS;
}
