#include "support/stream_busy_host.h"
int main(void)
{
    prepare_busy_uart();
    hal.stream.type = StreamType_Telnet;
    hal.stream.is_connected = busy_network_connected;
    busy_network_up = false;
    CHECK(!stream_is_busy(true));
    CHECK(busy_connection_queries == 1);
    return EXIT_SUCCESS;
}
