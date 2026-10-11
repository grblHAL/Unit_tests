#include "support/multi_spindle_host.h"
#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle();
    grbl.on_settings_changed = changed_settings;
    CHECK(store_setting(Setting_SpindleType, "2") == Status_OK);
    CHECK(settings.spindle.ref_id == 30);
    CHECK(spindle_get(0)->id == 2);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
