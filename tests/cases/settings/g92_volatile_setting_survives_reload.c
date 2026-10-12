#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2.0f);
    for(unsigned enabled = 0; enabled < 2; enabled++) {
        CHECK(store_setting(Setting_DisableG92Persistence, enabled ? "1" : "0") == Status_OK);
        CHECK(settings.flags.g92_is_volatile == enabled);
        settings.flags.g92_is_volatile = !enabled;
        settings_init();
        CHECK(settings.flags.g92_is_volatile == enabled);
        const setting_detail_t *detail = setting_get_details(Setting_DisableG92Persistence, NULL);
        CHECK(detail != NULL);
        CHECK(strcmp(setting_get_value(detail, 0), enabled ? "1" : "0") == 0);
    }
    return EXIT_SUCCESS;
}
