#include "support/stream_busy_host.h"
int main(void)
{
    prepare_busy_uart();
    uart_status.last_status_request = 1;
    engine_ticks = 6000;
    gc_state.file_run = true;
    CHECK(stream_is_busy(true));
    gc_state.file_run = false;
    CHECK(!stream_is_busy(true));
    return EXIT_SUCCESS;
}
