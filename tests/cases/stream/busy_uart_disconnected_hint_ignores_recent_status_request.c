#include "support/stream_busy_host.h"
int main(void)
{
    prepare_busy_uart();
    uart_status.last_status_request = 100;
    engine_ticks = 101;
    CHECK(!stream_is_busy(false));
    return EXIT_SUCCESS;
}
