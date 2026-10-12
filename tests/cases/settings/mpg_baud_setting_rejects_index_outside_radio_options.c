#include "support/mpg_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_settings(false);
    settings.mpg_baud_rate = 1;
    CHECK(store_setting(Settings_MPG_BaudRate, "6") == Status_SettingValueOutOfRange);
    CHECK(settings.mpg_baud_rate == 1);
    CHECK(pendant_baud_calls == 0);
    CHECK(change_callbacks == 0);
    return EXIT_SUCCESS;
}
