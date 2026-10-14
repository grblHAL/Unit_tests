#include "support/stream_allocator_host.h"
int main(void)
{
    prepare_stream_connections(); observe_stream_allocations = true;
    CHECK(stream_connect(&secondary_connection));
    unsigned changes = connection_changes;
    CHECK(!stream_connect(&secondary_connection));
    CHECK(stream_allocation_calls == 2 && stream_node_frees == 1);
    CHECK(connection_changes == changes && hal.stream.write == secondary_write);
    stream_disconnect(&secondary_connection); CHECK(stream_node_frees == 2);
    return EXIT_SUCCESS;
}
