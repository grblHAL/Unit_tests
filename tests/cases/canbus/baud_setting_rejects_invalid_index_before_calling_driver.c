#include "support/can_settings_host.h"

int main(void)
{
    prepare_can_settings();
    settings.canbus_baud = 2;
    CHECK(store_setting(Setting_CANbus_BaudRate, "4") == Status_SettingValueOutOfRange);
    CHECK(can_baud_calls == 0 && settings.canbus_baud == 2);
    return EXIT_SUCCESS;
}
