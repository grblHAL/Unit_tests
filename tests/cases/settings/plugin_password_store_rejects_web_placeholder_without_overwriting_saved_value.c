#include "support/plugin_text_settings_host.h"
int main(void)
{
    prepare_plugin_text_settings();
    CHECK(store_setting((setting_id_t)1002, "new-sample") == Status_OK);
    const setting_detail_t *detail = setting_get_details((setting_id_t)1002, NULL);
    CHECK(detail && strcmp(setting_get_value(detail, 0), "new-sample") == 0);
    hal.stream.state.webui_connected = true;
    CHECK(strcmp(setting_get_value(detail, 0), PASSWORD_MASK) == 0);
    CHECK(store_setting((setting_id_t)1002, PASSWORD_MASK) == Status_InvalidStatement);
    CHECK(strcmp(plugin_password, "new-sample") == 0);
    CHECK(strcmp(saved_plugin_password, "new-sample") == 0);
    CHECK(plugin_text_saves == 1 && plugin_text_changes == 1);
    CHECK(strcmp(plugin_label, "router") == 0);
    return EXIT_SUCCESS;
}
