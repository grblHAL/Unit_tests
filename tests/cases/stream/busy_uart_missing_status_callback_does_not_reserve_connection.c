#include "support/stream_busy_host.h"
int main(void)
{
    prepare_busy_uart();
    uart_property.get_status = NULL;
    CHECK(!stream_is_busy(true));
    return EXIT_SUCCESS;
}
