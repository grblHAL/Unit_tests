#include "support/stream_connection_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_connections();
    CHECK(stream_connect(&secondary_connection));
    io_stream_t unknown = secondary_connection;
    stream_disconnect(&unknown);
    CHECK(hal.stream.type == StreamType_Telnet);
    CHECK(connection_changes == 2);
    clear_connection_output();
    hal.stream.write("reply");
    CHECK(strcmp(secondary_output, "reply") == 0);
    return EXIT_SUCCESS;
}
