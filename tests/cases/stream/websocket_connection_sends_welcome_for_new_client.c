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
    return EXIT_SUCCESS;
}
