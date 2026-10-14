#include "support/stream_allocator_host.h"
int main(void)
{
    prepare_report(); observe_stream_allocations = true; reject_stream_allocations = 1;
    bool connected = stream_connect(&primary_connection);
    observe_stream_allocations = false;
    CHECK(connected);
    CHECK(stream_allocation_calls == 0 && rejected_stream_allocations == 0);
    CHECK(reject_stream_allocations == 1 && hal.stream.write == primary_write);
    observe_stream_allocations = false; reject_stream_allocations = 0;
    primary_output[0] = 0; hal.stream.write_all("primary");
    CHECK(strcmp(primary_output,"primary") == 0);
    return EXIT_SUCCESS;
}
