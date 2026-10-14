#include "support/stream_busy_host.h"
int main(void)
{
    prepare_busy_uart();
    uart_status.last_status_request = 1;
    engine_ticks = 5001;
    CHECK(!stream_is_busy(true));
    return EXIT_SUCCESS;
}
