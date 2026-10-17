#include "support/settings_initialized_host.h"
int main(void)
{
    prepare_initialized_settings(2);
    CHECK(setting_get_details(Setting_DoorOptions, NULL) == NULL);
    CHECK(store_setting(Setting_DoorOptions, "1") == Status_SettingDisabled);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
