#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    stored_line_t original = "G21G90", result;
    settings_write_startup_line(0, original);
    settings_restore((settings_restore_t){ .defaults = true });
    CHECK(settings_read_startup_line(0, result));
    CHECK(strcmp(result, original) == 0);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
