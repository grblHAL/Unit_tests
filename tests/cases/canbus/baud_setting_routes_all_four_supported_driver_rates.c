#include "support/can_settings_host.h"

int main(void)
{
    prepare_can_settings();
    const uint32_t rates[] = {125000, 250000, 500000, 1000000};
    for(unsigned i = 0; i < 4; i++) {
        char value[] = {(char)('0' + i), '\0'};
        CHECK(store_setting(Setting_CANbus_BaudRate, value) == Status_OK);
        CHECK(selected_can_baud == rates[i] && can_baud_calls == i + 1);
        CHECK(settings.canbus_baud == i);
        const setting_detail_t *detail = setting_get_details(Setting_CANbus_BaudRate, NULL);
        CHECK(detail && setting_get_int_value(detail, 0) == i);
    }
    return EXIT_SUCCESS;
}
