#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    stored_line_t original = "custom-router-controller", loaded = {0};
    settings_write_build_info(original);
    settings_restore((settings_restore_t){.defaults = true});
    CHECK(settings_read_build_info(loaded)); CHECK(strcmp(loaded, original) == 0);
    return EXIT_SUCCESS;
}
