#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_prepare();
    for (unsigned round = 0; round < 3; round++)
    {
        for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
            stmh7_receive('A' + i % 26);
        stmh7_receive('z');
        CHECK(stmh7_stream->get_rx_buffer_count() == RX_BUFFER_SIZE - 1 &&
              !stmh7_stream->get_rx_buffer_free());
        for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
            CHECK(stmh7_stream->read() == 'A' + (int)(i % 26));
        CHECK(stmh7_stream->read() == SERIAL_NO_DATA);
    }
    return 0;
}
