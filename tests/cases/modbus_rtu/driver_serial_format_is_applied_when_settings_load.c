#include "support/rtu_host.h"

static unsigned driver_format_calls;
static serial_format_t driver_format;
static bool configure_driver_format(serial_format_t format)
{
    driver_format = format;
    driver_format_calls++;
    return true;
}
static void install_serial_format(void)
{
    rtu_stream_format = configure_driver_format;
    settings.modbus_stream_format.parity = Serial_ParityEven;
    settings.modbus_stream_format.width = 1;
    settings.modbus_stream_format.stopbits = 1;
}
int main(void)
{
    prepare_rtu_transport(NULL, -2, install_serial_format);
    CHECK(driver_format_calls == 1);
    CHECK(driver_format.parity == Serial_ParityEven);
    CHECK(driver_format.width == 1 && driver_format.stopbits == 1);
    send_request();
    inject_reply(false);
    poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 0);
    return EXIT_SUCCESS;
}
