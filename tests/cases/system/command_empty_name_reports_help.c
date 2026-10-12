#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$") == Status_OK);
    CHECK(strncmp(engine_output, "[HLP:", 5) == 0);
    CHECK(strstr(engine_output, "]" ASCII_EOL) != NULL);
    return EXIT_SUCCESS;
}
