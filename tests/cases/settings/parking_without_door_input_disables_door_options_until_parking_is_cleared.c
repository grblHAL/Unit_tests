#include "support/settings_initialized_host.h"
int main(void)
{
    prepare_initialized_settings(2);
    CHECK(!hal.signals_cap.safety_door_ajar);
    CHECK(store_setting(Setting_ParkingEnable, "0") == Status_OK);
    CHECK(setting_get_details(Setting_DoorOptions, NULL) != NULL);
    CHECK(store_setting(Setting_DoorOptions, "2") == Status_OK);
    CHECK(settings.safety_door.flags.keep_coolant_on);
    CHECK(store_setting(Setting_ParkingEnable, "1") == Status_OK);
    CHECK(settings.parking.flags.enabled);
    CHECK(setting_get_details(Setting_DoorOptions, NULL) == NULL);
    unsigned notifications = change_callbacks;
    CHECK(store_setting(Setting_DoorOptions, "0") == Status_SettingDisabled);
    CHECK(change_callbacks == notifications && settings.safety_door.flags.keep_coolant_on);
    CHECK(store_setting(Setting_ParkingEnable, "0") == Status_OK);
    CHECK(setting_get_details(Setting_DoorOptions, NULL) != NULL);
    CHECK(store_setting(Setting_DoorOptions, "0") == Status_OK);
    CHECK(!settings.safety_door.flags.keep_coolant_on && !settings.parking.flags.enabled);
    return EXIT_SUCCESS;
}
