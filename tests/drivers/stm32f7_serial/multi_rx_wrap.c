#include "stm7_serial_host.h"
int main(void)
{
    stm7_triplex_prepare();
    for (unsigned round = 0; round < 3; round++)
    {
        for (unsigned n = 0; n < 3; n++)
        {
            for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
                stm7_receive_port(n, 'A' + n);
            stm7_receive_port(n, 'z');
            CHECK(stm7_port_stream[n]->get_rx_buffer_count() == RX_BUFFER_SIZE - 1 &&
                  !stm7_port_stream[n]->get_rx_buffer_free());
        }
        for (unsigned n = 0; n < 3; n++)
        {
            for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
                CHECK(stm7_port_stream[n]->read() == 'A' + (int)n);
            CHECK(stm7_port_stream[n]->read() == SERIAL_NO_DATA);
        }
    }
    return 0;
}
