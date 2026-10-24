#include "sam_host.h"
int main(void)
{
    sam_prepare();
    unsigned clocks = sam_clocks, irqs = sam_irqs;
    CHECK(stream_close(sam_stream[1]));
    CHECK(!stream_close(sam_stream[1]));
    const io_stream_t *next = stream_open_instance(1, 19200, NULL, NULL);
    CHECK(next && next == sam_stream[1] && sam_clocks == clocks && sam_irqs == irqs);
    CHECK(stream_get_uart_status(1)->baud_rate == 19200 &&
          !stream_open_instance(1, 9600, NULL, NULL));
    return 0;
}
