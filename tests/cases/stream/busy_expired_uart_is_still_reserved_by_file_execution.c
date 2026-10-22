#include "support/stream_busy_host.h"
int main(void)
{
    prepare_busy_uart();
    uart_status.last_status_request = 1;
    engine_ticks = 6000;
    HOST_PARSER_FLAGS.file_run = true;
    CHECK(stream_is_busy(true));
    HOST_PARSER_FLAGS.file_run = false;
    CHECK(!stream_is_busy(true));
    return EXIT_SUCCESS;
}
