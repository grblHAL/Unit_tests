#include "support/plugin_numeric_settings_host.h"
int main(void)
{
    prepare_numeric_plugin();
    CHECK(store_setting((setting_id_t)1003, "42") == Status_OK);
    settings_restore((settings_restore_t){.defaults = On});
    CHECK(numeric_saves == 1 && numeric_notifications == 1);
    CHECK(numeric_live.byte == 42 && numeric_saved.byte == 42);
    CHECK(numeric_live.axes == X_AXIS_BIT && numeric_live.word == 1000);
    CHECK(numeric_live.integer == 123456 && numeric_live.enabled == 1);
    NEAR(numeric_live.decimal, 1.25f);
    return EXIT_SUCCESS;
}
