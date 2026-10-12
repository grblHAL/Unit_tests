#include "support/multi_spindle_host.h"
#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    grbl.on_settings_changed = changed_settings;
    settings.spindle.ref_id = 10;
    CHECK(store_setting(Setting_SpindleType, "3") == Status_SettingValueOutOfRange);
    CHECK(settings.spindle.ref_id == 10);
    CHECK(spindle_get(0)->id == 0);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
