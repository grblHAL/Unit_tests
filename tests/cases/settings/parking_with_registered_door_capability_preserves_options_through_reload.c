#include "support/settings_initialized_host.h"
int main(void)
{
    prepare_settings_store();
    // The board advertises its door input before settings metadata initializes.
    hal.signals_cap.safety_door_ajar = true;
    report_init_fns();
    settings.version.id = SETTINGS_VERSION;
    hal.nvs.put_byte(0, SETTINGS_VERSION);
    settings_write_global();
    settings_init();
    CHECK(store_setting(Setting_ParkingEnable, "1") == Status_OK);
    CHECK(setting_get_details(Setting_DoorOptions, NULL) != NULL);
    CHECK(store_setting(Setting_DoorOptions, "3") == Status_OK);
    CHECK(settings.safety_door.flags.ignore_when_idle && settings.safety_door.flags.keep_coolant_on);
    settings_init();
    CHECK(settings.parking.flags.enabled);
    CHECK(settings.safety_door.flags.ignore_when_idle && settings.safety_door.flags.keep_coolant_on);
    const setting_detail_t *options = setting_get_details(Setting_DoorOptions, NULL);
    CHECK(options != NULL && strcmp(setting_get_value(options, 0), "3") == 0);
    CHECK(store_setting(Setting_DoorOptions, "0") == Status_OK);
    CHECK(!settings.safety_door.flags.ignore_when_idle && !settings.safety_door.flags.keep_coolant_on);
    return EXIT_SUCCESS;
}
