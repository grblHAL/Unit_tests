#include "support/multi_spindle_host.h"
#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    grbl.on_settings_changed = changed_settings;
    CHECK(store_setting(Setting_SpindleType, "1") == Status_OK);
    CHECK(settings.spindle.ref_id == 20);
    CHECK(spindle_get(0)->id == 1);
    CHECK(change_callbacks == 1);
    const setting_detail_t *setting = setting_get_details(Setting_SpindleType, NULL);
    CHECK(setting != NULL);
    CHECK(setting_get_int_value(setting, 0) == 1);
    return EXIT_SUCCESS;
}
