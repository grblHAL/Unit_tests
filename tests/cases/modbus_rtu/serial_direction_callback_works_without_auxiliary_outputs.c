#include "support/rtu_host.h"
static unsigned direction_calls;
static bool direction_log[4];
static void serial_direction(bool transmit)
{
    CHECK(direction_calls < 4);
    direction_log[direction_calls++] = transmit;
}
static void configure_serial_direction(void) { rtu_stream_direction = serial_direction; }
int main(void)
{
    prepare_rtu_transport(NULL, -1, configure_serial_direction);
    CHECK(hal.port.num_digital_out == 0);
    send_request();
    inject_reply(false);
    for(unsigned i = 0; i < 5 && rx_calls == 0; i++) poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 0);
    CHECK(direction_calls == 2);
    CHECK(direction_log[0] && !direction_log[1]);
    return EXIT_SUCCESS;
}
