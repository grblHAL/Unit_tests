#include "support/system_metadata_host.h"
#include "check.h"

int main(void)
{
    prepare_system_metadata();
    stored_line_t first_line = "G21";
    settings_write_startup_line(0, first_line);
    stored_line_t second_line = "G90";
    settings_write_startup_line(1, second_line);
    CHECK(system_command("$N") == Status_OK);
    CHECK(strcmp(metadata_output, "$N0=G21" ASCII_EOL "$N1=G90" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
