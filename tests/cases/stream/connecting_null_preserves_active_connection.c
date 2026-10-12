#include "support/stream_connection_host.h"
#include "check.h"

int main(void)
{
    prepare_stream_connections();
    CHECK(!stream_connect(NULL));
    CHECK(connection_changes == 1);
    CHECK(hal.stream.type == StreamType_Serial);
    CHECK(stream_get_base() == &primary_connection);
    return EXIT_SUCCESS;
}
