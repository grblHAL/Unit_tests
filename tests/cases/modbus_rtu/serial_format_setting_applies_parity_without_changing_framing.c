#include "support/rtu_host.h"
static serial_format_t captured_format;
static unsigned format_calls;
static bool capture_format(serial_format_t format) { captured_format = format; format_calls++; return true; }

int main(void)
{
    prepare_rtu();
    modbus_get_rtu_stream()->set_format = capture_format;
    settings.modbus_stream_format.width = 1;
    settings.modbus_stream_format.stopbits = 1;
    char even[] = "1", odd[] = "2";
    CHECK(settings_store_setting(Setting_ModBus_StreamFormat, even) == Status_OK);
    CHECK(format_calls == 1 && captured_format.parity == Serial_ParityEven);
    CHECK(captured_format.width == 1 && captured_format.stopbits == 1);
    const setting_detail_t *detail = setting_get_details(Setting_ModBus_StreamFormat, NULL);
    CHECK(detail != NULL && setting_get_int_value(detail, 0) == 1);
    CHECK(settings_store_setting(Setting_ModBus_StreamFormat, odd) == Status_OK);
    CHECK(format_calls == 2 && captured_format.parity == Serial_ParityOdd);
    CHECK(setting_get_int_value(detail, 0) == 2);
    return EXIT_SUCCESS;
}
