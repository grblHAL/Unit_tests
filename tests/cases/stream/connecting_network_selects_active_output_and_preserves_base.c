#include "support/stream_connection_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_connections();
    CHECK(stream_connect(&secondary_connection));
    CHECK(stream_get_base() == &primary_connection);
    CHECK(hal.stream.type == StreamType_Telnet);
    CHECK(secondary_rt == protocol_enqueue_realtime_command);
    CHECK(connection_changes == 2);
    clear_connection_output();
    hal.stream.write("reply");
    CHECK(strcmp(secondary_output, "reply") == 0);
    CHECK(primary_output[0] == '\0');
    return EXIT_SUCCESS;
}
