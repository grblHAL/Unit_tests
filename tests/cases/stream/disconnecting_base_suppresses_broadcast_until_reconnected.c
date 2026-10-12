#include "support/stream_connection_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_connections();
    CHECK(stream_connect(&secondary_connection));
    stream_disconnect(&primary_connection);
    clear_connection_output();
    hal.stream.write_all("first");
    CHECK(primary_output[0] == '\0');
    CHECK(strcmp(secondary_output, "first") == 0);
    CHECK(stream_connect(&primary_connection));
    clear_connection_output();
    hal.stream.write_all("second");
    CHECK(strcmp(primary_output, "second") == 0);
    CHECK(strcmp(secondary_output, "second") == 0);
    return EXIT_SUCCESS;
}
