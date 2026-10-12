#include "support/settings_validation_host.h"

int main(void)
{
    prepare_settings_store();
    char valid[] = "7", invalid[] = "8";
    CHECK(setting_validate(Setting_DirInvertMask, 7, valid) == Status_OK);
    CHECK(setting_validate(Setting_DirInvertMask, 8, invalid) == Status_SettingValueOutOfRange);
    CHECK(settings.steppers.dir_invert.mask == 0 && change_callbacks == 0);
    return EXIT_SUCCESS;
}
