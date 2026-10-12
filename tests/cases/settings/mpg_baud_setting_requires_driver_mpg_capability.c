#include "support/mpg_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_settings(false);
    hal.driver_cap.mpg_mode = false;
    settings.mpg_baud_rate = 1;
    CHECK(store_setting(Settings_MPG_BaudRate, "0") == Status_SettingDisabled);
    CHECK(settings.mpg_baud_rate == 1);
    CHECK(pendant_baud_calls == 0);
    return EXIT_SUCCESS;
}
