#include "support/stream_connection_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_connections();
    sys.driver_started = true;
    hal.stream.state.webui_connected = true;
    io_stream_t websocket = secondary_connection;
    websocket.type = StreamType_WebSocket;
    CHECK(stream_connect(&websocket));
    CHECK(secondary_output[0] == '\0');
    CHECK(strstr(primary_output, "WEBSOCKET STREAM ACTIVE") != NULL);
    return EXIT_SUCCESS;
}
