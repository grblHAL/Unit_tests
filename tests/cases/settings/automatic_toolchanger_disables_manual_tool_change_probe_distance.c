#include "support/settings_initialized_host.h"
#include "check.h"

int main(void)
{
    prepare_initialized_settings(2.0f);
    hal.driver_cap.atc = true;
    unsigned callbacks = change_callbacks;
    CHECK(setting_get_details(Setting_ToolChangeProbingDistance, NULL) == NULL);
    CHECK(store_setting(Setting_ToolChangeProbingDistance, "1") == Status_SettingDisabled);
    CHECK(change_callbacks == callbacks);
    return EXIT_SUCCESS;
}
