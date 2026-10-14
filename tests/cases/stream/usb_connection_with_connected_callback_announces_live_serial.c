#include "support/stream_connection_host.h"
int main(void)
{
    prepare_stream_connections();
    CHECK(stream_connect(&secondary_connection));
    io_stream_t usb = primary_connection;
    usb.instance = 2;
    usb.state.is_usb = true;
    clear_connection_output();
    CHECK(stream_connect(&usb));
    CHECK(hal.stream.state.is_usb && hal.stream.is_connected());
    CHECK(strstr(primary_output,"SERIAL STREAM ACTIVE") != NULL);
    stream_disconnect(&usb);
    stream_disconnect(&secondary_connection);
    return EXIT_SUCCESS;
}
