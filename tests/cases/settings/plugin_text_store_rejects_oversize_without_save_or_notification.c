#include "support/plugin_text_settings_host.h"
int main(void)
{
    prepare_plugin_text_settings();
    CHECK(store_setting((setting_id_t)1001, "1234567890123456") == Status_SettingValueOutOfRange);
    const setting_detail_t *detail = setting_get_details((setting_id_t)1001, NULL);
    CHECK(detail && strcmp(setting_get_value(detail, 0), "router") == 0);
    CHECK(plugin_text_saves == 0 && plugin_text_changes == 0);
    CHECK(strcmp(plugin_password, "sample-key") == 0);
    return EXIT_SUCCESS;
}
