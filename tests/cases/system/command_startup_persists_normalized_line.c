#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$N0=g21 g90") == Status_OK);
    stored_line_t line;
    CHECK(settings_read_startup_line(0, line));
    CHECK(strcmp(line, "G21G90") == 0);
    return EXIT_SUCCESS;
}
