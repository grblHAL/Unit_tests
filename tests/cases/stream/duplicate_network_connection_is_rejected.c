#include "support/stream_connection_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_connections();
    CHECK(stream_connect(&secondary_connection));
    CHECK(!stream_connect(&secondary_connection));
    CHECK(connection_changes == 2);
    clear_connection_output();
    hal.stream.write_all("status");
    CHECK(strcmp(secondary_output, "status") == 0);
    return EXIT_SUCCESS;
}
