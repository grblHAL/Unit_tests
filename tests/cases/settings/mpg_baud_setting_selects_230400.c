#include "support/mpg_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_mpg_settings(false);
    CHECK(store_setting(Settings_MPG_BaudRate, "2") == Status_OK);
    CHECK(settings.mpg_baud_rate == 2);
    CHECK(pendant_baud == 230400);
    CHECK(pendant_baud_calls == 1);
    CHECK(change_callbacks == 1);
    CHECK(setting_get_int_value(setting_get_details(Settings_MPG_BaudRate, NULL), 0) == 2);
    return EXIT_SUCCESS;
}
