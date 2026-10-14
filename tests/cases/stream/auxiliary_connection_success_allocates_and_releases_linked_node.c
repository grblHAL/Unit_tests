#include "support/stream_allocator_host.h"
int main(void)
{
    prepare_stream_connections(); observe_stream_allocations = true;
    CHECK(stream_connect(&secondary_connection));
    CHECK(stream_allocation_calls == 1 && rejected_stream_allocations == 0);
    stream_disconnect(&secondary_connection);
    CHECK(stream_node_frees == 1);
    clear_connection_output(); hal.stream.write_all("primary intact");
    CHECK(strcmp(primary_output,"primary intact") == 0 && secondary_output[0] == 0);
    return EXIT_SUCCESS;
}
