#include "support/stream_connection_host.h"
int main(void)
{
    prepare_stream_connections();
    CHECK(stream_connect(&secondary_connection));
    io_stream_t usb = primary_connection;
    usb.instance = 2;
    usb.state.is_usb = true;
    usb.is_connected = NULL;
    clear_connection_output();
    uint32_t before = engine_ticks;
    CHECK(stream_connect(&usb));
    CHECK(hal.stream.state.is_usb);
    CHECK(strstr(primary_output,"SERIAL STREAM ACTIVE") == NULL);
    CHECK(engine_ticks == before);
    stream_disconnect(&usb);
    stream_disconnect(&secondary_connection);
    return EXIT_SUCCESS;
}
