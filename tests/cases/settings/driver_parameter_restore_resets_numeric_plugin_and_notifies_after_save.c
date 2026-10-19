#include "support/plugin_numeric_settings_host.h"
int main(void)
{
    prepare_numeric_plugin();
    CHECK(store_setting((setting_id_t)1003, "42") == Status_OK);
    float core_steps = settings.axis[X_AXIS].steps_per_mm;
    settings_restore((settings_restore_t){.driver_parameters = On});
    CHECK(numeric_saves == 2 && numeric_notifications == 2);
    NEAR(numeric_live.decimal, 0);
    CHECK(numeric_live.axes == 0 && numeric_live.byte == 0 && numeric_live.word == 0);
    CHECK(numeric_live.integer == 0 && numeric_live.enabled == 0);
    CHECK(numeric_saved.byte == 0 && numeric_saved.integer == 0);
    NEAR(settings.axis[X_AXIS].steps_per_mm, core_steps);
    return EXIT_SUCCESS;
}
