#include "support/mpg_settings_host.h"

int main(void)
{
    prepare_mpg_settings(false);
    hal.step_us_min = 2.0f;
    settings.version.id = SETTINGS_VERSION;
    hal.nvs.put_byte(0, SETTINGS_VERSION);
    CHECK(store_setting(Settings_MPG_BaudRate, "3") == Status_OK);
    CHECK(pendant_baud == 460800 && pendant_baud_calls == 1);
    settings.version.build = 260904;
    settings.flags.settings_downgrade = false;
    settings.safety_door.coolant_on_delay = 1.25f;
    settings.coolant.on_delay = 50;
    settings.pwm_spindle.at_speed_tolerance = 4.5f;
    settings.spindle.at_speed_tolerance = 1.0f;
    settings_write_global();
    settings_init();
    CHECK(settings.version.build == GRBL_BUILD - 20000000UL);
    CHECK(settings.mpg_baud_rate == 3 && pendant_baud == 460800 && pendant_baud_calls == 2);
    CHECK(settings.coolant.on_delay == 50);
    NEAR(settings.spindle.at_speed_tolerance, 1.0f);
    NEAR(settings.pwm_spindle.at_speed_tolerance, 4.5f);
    settings_t saved = {0};
    CHECK(hal.nvs.memcpy_from_nvs((uint8_t *)&saved, NVS_ADDR_GLOBAL, sizeof(saved), true) == NVS_TransferResult_OK);
    CHECK(saved.version.build == settings.version.build && saved.mpg_baud_rate == 3);
    settings_init();
    CHECK(settings.mpg_baud_rate == 3 && pendant_baud_calls == 3 && pendant_baud == 460800);
    CHECK(settings.coolant.on_delay == 50);
    NEAR(settings.spindle.at_speed_tolerance, 1.0f);
    return EXIT_SUCCESS;
}
