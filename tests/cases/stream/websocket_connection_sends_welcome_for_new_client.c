#include "support/stream_connection_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_connections();
    sys.driver_started = true;
    io_stream_t websocket = secondary_connection;
    websocket.type = StreamType_WebSocket;
    CHECK(stream_connect(&websocket));
    CHECK(hal.stream.type == StreamType_WebSocket);
    CHECK(strstr(secondary_output, "GrblHAL " GRBL_VERSION) != NULL);
    CHECK(strstr(primary_output, "WEBSOCKET STREAM ACTIVE") != NULL);
    stream_disconnect(&websocket);
    primary_up = false;
    clear_connection_output();
    CHECK(stream_connect(&websocket));
    CHECK(hal.stream.type == StreamType_WebSocket && hal.stream.is_connected());
    CHECK(strstr(secondary_output, "GrblHAL " GRBL_VERSION) != NULL);
    CHECK(primary_output[0] == '\0');
    clear_connection_output();
    hal.stream.write_all("status");
    CHECK(strcmp(secondary_output, "status") == 0 && primary_output[0] == '\0');
    primary_up = true;
    stream_disconnect(&websocket);
    return EXIT_SUCCESS;
}
