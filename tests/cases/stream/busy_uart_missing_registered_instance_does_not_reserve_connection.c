#include "support/stream_busy_host.h"
int main(void)
{
    prepare_busy_uart();
    hal.stream.instance = 9;
    CHECK(!stream_is_busy(true));
    return EXIT_SUCCESS;
}
