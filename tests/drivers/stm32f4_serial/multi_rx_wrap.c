#include "stm_serial_host.h"
int main(void)
{
    stm_triplex_prepare();
    for (unsigned round = 0; round < 3; round++)
    {
        for (unsigned n = 0; n < 3; n++)
        {
            for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
                stm_receive_port(n, 'A' + n);
            stm_receive_port(n, 'z');
            CHECK(stm_port_stream[n]->get_rx_buffer_count() == RX_BUFFER_SIZE - 1 &&
                  !stm_port_stream[n]->get_rx_buffer_free());
        }
        for (unsigned n = 0; n < 3; n++)
        {
            for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
                CHECK(stm_port_stream[n]->read() == 'A' + (int)n);
            CHECK(stm_port_stream[n]->read() == SERIAL_NO_DATA);
        }
    }
    return 0;
}
