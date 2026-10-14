#include "support/stream_busy_host.h"
int main(void)
{
    prepare_busy_uart();
    hal.stream.type = uart_property.type = StreamType_Bluetooth;
    uart_status.last_status_request = 100;
    engine_ticks = 101;
    CHECK(stream_is_busy(true));
    engine_ticks = 5100;
    CHECK(!stream_is_busy(true));
    return EXIT_SUCCESS;
}
