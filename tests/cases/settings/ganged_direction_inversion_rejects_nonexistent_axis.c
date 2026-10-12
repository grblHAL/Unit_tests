#include "support/ganged_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_ganged_settings();
    settings.steppers.ganged_dir_invert.mask = 5;
    CHECK(store_setting(Setting_GangedDirInvertMask, "8") == Status_SettingValueOutOfRange);
    CHECK(settings.steppers.ganged_dir_invert.mask == 5);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
