#include "support/stream_busy_host.h"
int main(void)
{
    prepare_busy_uart();
    uart_status.last_status_request = 0;
    engine_ticks = 100;
    CHECK(!stream_is_busy(true));
    return EXIT_SUCCESS;
}
