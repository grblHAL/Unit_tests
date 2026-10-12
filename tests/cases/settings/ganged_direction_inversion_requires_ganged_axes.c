#include "support/ganged_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_ganged_settings();
    configured_ganged_axes.mask = 0;
    settings.steppers.ganged_dir_invert.mask = 5;
    CHECK(store_setting(Setting_GangedDirInvertMask, "1") == Status_SettingDisabled);
    CHECK(settings.steppers.ganged_dir_invert.mask == 5);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
