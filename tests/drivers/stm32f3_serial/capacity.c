#include "stm3_serial_host.h"
int main(void)
{
    stm3_prepare();
    CHECK(stm3_stream->get_rx_buffer_free() == RX_BUFFER_SIZE - 1);
    for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
        stm3_receive('A');
    CHECK(stm3_stream->get_rx_buffer_free() == 0);
    CHECK(stm3_stream->read() == 'A' && stm3_stream->get_rx_buffer_free() == 1);
    return 0;
}
