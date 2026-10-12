#include "support/settings_host.h"
#include "check.h"

int main(void)
{
    prepare_settings_store();
    CHECK(store_setting(Setting_DirInvertMask, "5") == Status_OK);
    CHECK(settings.steppers.dir_invert.bits == 5);
    CHECK(store_setting(Setting_DirInvertMask, "8") == Status_SettingValueOutOfRange);
    CHECK(settings.steppers.dir_invert.bits == 5);
    CHECK(change_callbacks == 1);
    return EXIT_SUCCESS;
}
