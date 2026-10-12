#include "support/stream_connection_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_connections();
    CHECK(stream_connect(&secondary_connection));
    clear_connection_output();
    hal.stream.write_all("status");
    CHECK(strcmp(primary_output, "status") == 0);
    CHECK(strcmp(secondary_output, "status") == 0);
    return EXIT_SUCCESS;
}
