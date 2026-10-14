#include "support/stream_busy_host.h"
int main(void)
{
    prepare_busy_uart();
    hal.stream.type = StreamType_WebSocket;
    hal.stream.is_connected = busy_network_connected;
    busy_network_up = true;
    CHECK(!stream_is_busy(false));
    CHECK(busy_connection_queries == 0);
    return EXIT_SUCCESS;
}
