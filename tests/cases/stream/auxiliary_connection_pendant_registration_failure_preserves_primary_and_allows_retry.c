#include "support/stream_allocator_host.h"
#include "support/mpg_stream_host.h"

int main(void)
{
    prepare_mpg_stream();
    observe_stream_allocations = true;
    reject_stream_allocations = 1;
    bool registered = stream_mpg_register(&pendant_device, false, stream_mpg_check_enable);
    observe_stream_allocations = false;
    CHECK(!registered && rejected_stream_allocations == 1);
    CHECK(stream_allocation_calls == 1 && registered_calls == 0);
    CHECK(hal.stream.read == primary_input && hal.stream.write == primary_write);
    primary_output[0] = pendant_output[0] = '\0';
    hal.stream.write_all("primary intact");
    CHECK(strcmp(primary_output, "primary intact") == 0 && pendant_output[0] == '\0');
    CHECK(stream_mpg_register(&pendant_device, false, stream_mpg_check_enable));
    CHECK(registered_calls == 1 && pendant_tx_capable);
    CHECK(!sys.mpg_mode && hal.stream.read == primary_input);
    primary_output[0] = pendant_output[0] = '\0';
    hal.stream.write_all("connected");
    CHECK(strcmp(primary_output, "connected") == 0);
    CHECK(strcmp(pendant_output, "connected") == 0);
    pendant_output[0] = '\0';
    CHECK(pendant_rt(CMD_GCODE_REPORT));
    engine_execute_tasks(STATE_IDLE);
    CHECK(strstr(pendant_output, "[GC:") != NULL);
    CHECK(strcmp(primary_output, "connected") == 0);
    return EXIT_SUCCESS;
}
