#include "support/system_metadata_host.h"
#include "check.h"

int main(void)
{
    prepare_system_metadata();
    settings_write_startup_line(0, "G21");
    CHECK(system_command("$N1=G90") == Status_OK);
    char line[sizeof(stored_line_t)];
    CHECK(settings_read_startup_line(0, line));
    CHECK(strcmp(line, "G21") == 0);
    CHECK(settings_read_startup_line(1, line));
    CHECK(strcmp(line, "G90") == 0);
    return EXIT_SUCCESS;
}
