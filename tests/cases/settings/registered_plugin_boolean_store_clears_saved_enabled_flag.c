#include "support/plugin_numeric_settings_host.h"
int main(void)
{
    prepare_numeric_plugin();
    CHECK(store_setting((setting_id_t)1006, "0") == Status_OK);
    CHECK(numeric_live.enabled == 0 && numeric_saved.enabled == 0);
    CHECK(numeric_saves == 1 && numeric_notifications == 1);
    CHECK(numeric_live.axes == X_AXIS_BIT && numeric_live.integer == 123456);
    return EXIT_SUCCESS;
}
