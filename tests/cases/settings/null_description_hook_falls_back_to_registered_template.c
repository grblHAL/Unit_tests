#include "support/settings_registry_host.h"
#include "check.h"
static unsigned hook_calls;
static const char *missing_description(setting_id_t id) { CHECK(id == (setting_id_t)1005); hook_calls++; return NULL; }
int main(void)
{
    prepare_settings_registry();
    grbl.on_setting_get_description = missing_description;
    CHECK(strcmp(setting_get_description((setting_id_t)1005), "Channel 5 calibration") == 0);
    CHECK(hook_calls == 1);
    return EXIT_SUCCESS;
}
