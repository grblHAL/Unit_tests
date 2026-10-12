#include "support/ganged_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_ganged_settings();
    settings.steppers.ganged_dir_invert.mask = 5;
    CHECK(store_setting(Setting_GangedDirInvertMask, "0") == Status_OK);
    CHECK(settings.steppers.ganged_dir_invert.mask == 0);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
