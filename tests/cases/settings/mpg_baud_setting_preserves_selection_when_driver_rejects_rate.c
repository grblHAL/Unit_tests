#include "support/mpg_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_settings(true);
    settings.mpg_baud_rate = 1;
    CHECK(store_setting(Settings_MPG_BaudRate, "5") == Status_SettingValueOutOfRange);
    CHECK(settings.mpg_baud_rate == 1);
    CHECK(pendant_baud_calls == 1);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
