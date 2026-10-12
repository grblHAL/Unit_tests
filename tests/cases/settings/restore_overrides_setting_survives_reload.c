#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2.0f);
    for(unsigned enabled = 0; enabled < 2; enabled++) {
        CHECK(store_setting(Setting_RestoreOverrides, enabled ? "1" : "0") == Status_OK);
        CHECK(settings.flags.restore_overrides == enabled);
        settings.flags.restore_overrides = !enabled;
        settings_init();
        CHECK(settings.flags.restore_overrides == enabled);
        const setting_detail_t *detail = setting_get_details(Setting_RestoreOverrides, NULL);
        CHECK(detail != NULL);
        CHECK(strcmp(setting_get_value(detail, 0), enabled ? "1" : "0") == 0);
    }
    return EXIT_SUCCESS;
}
