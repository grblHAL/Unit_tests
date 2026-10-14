#include "support/stream_busy_host.h"
int main(void)
{
    prepare_busy_uart();
    uart_status.last_status_request = UINT32_MAX - 100;
    engine_ticks = 100;
    CHECK(stream_is_busy(true));
    return EXIT_SUCCESS;
}
