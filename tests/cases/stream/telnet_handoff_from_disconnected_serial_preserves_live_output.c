#include "support/stream_connection_host.h"

int main(void)
{
    prepare_stream_connections();
    primary_up = false;
    clear_connection_output();
    CHECK(stream_connect(&secondary_connection));
    CHECK(stream_get_base() == &primary_connection);
    CHECK(hal.stream.type == StreamType_Telnet && hal.stream.is_connected());
    CHECK(primary_output[0] == '\0' && secondary_output[0] == '\0');
    CHECK(connection_changes == 2 && secondary_rt == protocol_enqueue_realtime_command);
    hal.stream.write("reply");
    CHECK(strcmp(secondary_output, "reply") == 0 && primary_output[0] == '\0');
    clear_connection_output();
    hal.stream.write_all("status");
    CHECK(strcmp(secondary_output, "status") == 0 && primary_output[0] == '\0');
    primary_up = true;
    stream_disconnect(&secondary_connection);
    CHECK(hal.stream.type == StreamType_Serial && hal.stream.is_connected());
    clear_connection_output();
    hal.stream.write("serial restored");
    CHECK(strcmp(primary_output, "serial restored") == 0 && secondary_output[0] == '\0');
    return EXIT_SUCCESS;
}
