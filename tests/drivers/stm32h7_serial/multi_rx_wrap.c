#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_triplex_prepare();
    for (unsigned round = 0; round < 3; round++)
    {
        for (unsigned n = 0; n < 3; n++)
        {
            for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
                stmh7_receive_port(n, 'A' + n);
            stmh7_receive_port(n, 'z');
            CHECK(stmh7_port_stream[n]->get_rx_buffer_count() == RX_BUFFER_SIZE - 1 &&
                  !stmh7_port_stream[n]->get_rx_buffer_free());
        }
        for (unsigned n = 0; n < 3; n++)
        {
            for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
                CHECK(stmh7_port_stream[n]->read() == 'A' + (int)n);
            CHECK(stmh7_port_stream[n]->read() == SERIAL_NO_DATA);
        }
    }
    return 0;
}
