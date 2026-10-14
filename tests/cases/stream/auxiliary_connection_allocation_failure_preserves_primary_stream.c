#include "support/stream_allocator_host.h"
int main(void)
{
    prepare_stream_connections();
    unsigned changes = connection_changes;
    observe_stream_allocations = true; reject_stream_allocations = 1;
    CHECK(!stream_connect(&secondary_connection));
    CHECK(rejected_stream_allocations == 1 && connection_changes == changes);
    CHECK(hal.stream.write == primary_write);
    clear_connection_output(); hal.stream.write_all("primary intact");
    CHECK(strcmp(primary_output,"primary intact") == 0 && secondary_output[0] == 0);
    return EXIT_SUCCESS;
}
