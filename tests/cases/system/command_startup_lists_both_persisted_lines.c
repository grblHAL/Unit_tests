#include "support/system_metadata_host.h"
#include "check.h"

int main(void)
{
    prepare_system_metadata();
    settings_write_startup_line(0, "G21");
    settings_write_startup_line(1, "G90");
    CHECK(system_command("$N") == Status_OK);
    CHECK(strcmp(metadata_output, "$N0=G21" ASCII_EOL "$N1=G90" ASCII_EOL) == 0);
    return EXIT_SUCCESS;
}
