#include "support/stream_connection_host.h"
int main(void)
{
    prepare_stream_connections();
    CHECK(stream_connect(&secondary_connection));
    io_stream_t serial = primary_connection;
    serial.instance = 2;
    serial.is_connected = NULL;
    clear_connection_output();
    uint32_t before = engine_ticks;
    CHECK(stream_connect(&serial));
    CHECK(hal.stream.type == StreamType_Serial && hal.stream.is_connected());
    CHECK(strstr(primary_output,"SERIAL STREAM ACTIVE") != NULL);
    CHECK(engine_ticks - before == 100);
    stream_disconnect(&serial);
    stream_disconnect(&secondary_connection);
    return EXIT_SUCCESS;
}
