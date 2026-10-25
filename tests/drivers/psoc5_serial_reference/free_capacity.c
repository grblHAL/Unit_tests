#include "psoc_host.h"
int main(void)
{
    psoc_start();
    uint16_t free = psoc_stream->get_rx_buffer_free();
    fprintf(stderr, "Reported free=%u, usable capacity=%u\n", free, RX_BUFFER_SIZE - 1);
    CHECK(free == RX_BUFFER_SIZE - 1);
    return 0;
}
