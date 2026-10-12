#include "support/rtu_host.h"
static uint32_t selected_baud;
static unsigned baud_calls;
static bool capture_baud(uint32_t baud) { selected_baud = baud; baud_calls++; return true; }

int main(void)
{
    prepare_rtu();
    modbus_get_rtu_stream()->set_baud_rate = capture_baud;
    char slow[] = "0", fast[] = "5";
    CHECK(settings_store_setting(Settings_ModBus_BaudRate, slow) == Status_OK);
    CHECK(selected_baud == 2400 && baud_calls == 1);
    const setting_detail_t *detail = setting_get_details(Settings_ModBus_BaudRate, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 0);
    CHECK(settings_store_setting(Settings_ModBus_BaudRate, fast) == Status_OK);
    CHECK(selected_baud == 115200 && baud_calls == 2);
    CHECK(setting_get_int_value(detail, 0) == 5);
    return EXIT_SUCCESS;
}
