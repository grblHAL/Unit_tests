#include "support/plugin_numeric_settings_host.h"
int main(void)
{
    prepare_numeric_plugin();
    CHECK(store_setting((setting_id_t)1001, "3.125") == Status_OK);
    NEAR(numeric_live.decimal, 3.125f);
    CHECK(numeric_saves == 1 && numeric_notifications == 1);
    const setting_detail_t *detail = setting_get_details((setting_id_t)1001, NULL);
    CHECK(detail != NULL && strcmp(setting_get_value(detail, 0), "3.125") == 0);
    CHECK(numeric_live.byte == 7 && numeric_live.word == 1000 && numeric_live.integer == 123456);
    return EXIT_SUCCESS;
}
