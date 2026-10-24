#include "sam_host.h"
int main(void)
{
    sam_prepare();
    for (unsigned n = 0; n < 2; n++)
    {
        sam_receive(n, 'G');
        sam_receive(n, '1');
        sam_stream[n]->cancel_read_buffer();
        CHECK(sam_stream[n]->get_rx_buffer_count() == 1 && sam_stream[n]->read() == ASCII_CAN &&
              sam_stream[n]->read() == SERIAL_NO_DATA);
        sam_receive(n, 'X');
        sam_stream[n]->reset_read_buffer();
        CHECK(!sam_stream[n]->get_rx_buffer_count() &&
              sam_stream[n]->get_rx_buffer_free() == RX_BUFFER_SIZE - 1);
    }
    return 0;
}
