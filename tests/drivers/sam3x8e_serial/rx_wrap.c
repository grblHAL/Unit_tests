#include "sam_host.h"
int main(void)
{
    sam_prepare();
    for (unsigned n = 0; n < 2; n++)
    {
        for (unsigned round = 0; round < 3; round++)
        {
            for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
                sam_receive(n, 'A' + i % 26);
            sam_receive(n, 'z');
            CHECK(sam_stream[n]->get_rx_buffer_count() == RX_BUFFER_SIZE - 1 &&
                  !sam_stream[n]->get_rx_buffer_free());
            for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
                CHECK(sam_stream[n]->read() == 'A' + (int)(i % 26));
            CHECK(sam_stream[n]->read() == SERIAL_NO_DATA);
        }
    }
    return 0;
}
