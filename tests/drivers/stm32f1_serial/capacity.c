#include "stm1_serial_host.h"
int main(void)
{
    stm1_prepare();
    CHECK(stm1_stream->get_rx_buffer_free() == RX_BUFFER_SIZE - 1);
    for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
        stm1_receive('A');
    CHECK(stm1_stream->get_rx_buffer_free() == 0);
    CHECK(stm1_stream->read() == 'A' && stm1_stream->get_rx_buffer_free() == 1);
    return 0;
}
