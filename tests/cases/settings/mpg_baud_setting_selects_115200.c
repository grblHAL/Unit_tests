#include "support/mpg_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_settings(false);
    CHECK(store_setting(Settings_MPG_BaudRate, "1") == Status_OK);
    CHECK(settings.mpg_baud_rate == 1);
    CHECK(pendant_baud == 115200);
    CHECK(pendant_baud_calls == 1);
    CHECK(change_callbacks == 1);
    CHECK(setting_get_int_value(setting_get_details(Settings_MPG_BaudRate, NULL), 0) == 1);
    return EXIT_SUCCESS;
}
