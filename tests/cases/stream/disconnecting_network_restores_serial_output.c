#include "support/stream_connection_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_connections();
    CHECK(stream_connect(&secondary_connection));
    stream_disconnect(&primary_connection);
    clear_connection_output();
    hal.stream.write_all("network-only");
    CHECK(primary_output[0] == '\0');
    CHECK(strcmp(secondary_output, "network-only") == 0);
    stream_disconnect(&secondary_connection);
    CHECK(hal.stream.type == StreamType_Serial);
    CHECK(hal.stream.is_connected());
    CHECK(connection_changes == 3);
    clear_connection_output();
    hal.stream.write_all("status");
    CHECK(strcmp(primary_output, "status") == 0);
    CHECK(secondary_output[0] == '\0');
    return EXIT_SUCCESS;
}
