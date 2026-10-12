#include "support/system_command_host.h"
#include "check.h"

int main(void)
{
    prepare_system_command();
    CHECK(system_command("$I=Bench controller") == Status_OK);
    stored_line_t line;
    CHECK(settings_read_build_info(line));
    CHECK(strcmp(line, "Bench controller") == 0);
    return EXIT_SUCCESS;
}
