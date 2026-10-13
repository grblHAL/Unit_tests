#include "support/can_settings_host.h"

int main(void)
{
    prepare_can_settings();
    accept_can_baud = false;
    CHECK(store_setting(Setting_CANbus_BaudRate, "3") == Status_SettingValueOutOfRange);
    CHECK(can_baud_calls == 1 && selected_can_baud == 1000000);
    accept_can_baud = true;
    CHECK(store_setting(Setting_CANbus_BaudRate, "1") == Status_OK);
    CHECK(can_baud_calls == 2 && selected_can_baud == 250000);
    return EXIT_SUCCESS;
}
