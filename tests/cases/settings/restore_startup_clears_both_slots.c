#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    stored_line_t first = "G21", second = "G90", result;
    settings_write_startup_line(0, first);
    settings_write_startup_line(1, second);
    settings_restore((settings_restore_t){ .startup_lines = true });
    CHECK(settings_read_startup_line(0, result) && result[0] == 0);
    CHECK(settings_read_startup_line(1, result) && result[0] == 0);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
