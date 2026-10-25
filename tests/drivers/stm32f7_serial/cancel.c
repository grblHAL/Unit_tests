#include "stm7_serial_host.h"
int main(void)
{
    stm7_prepare();
    stm7_receive('G');
    stm7_receive('1');
    stm7_stream->cancel_read_buffer();
    CHECK(stm7_stream->read() == ASCII_CAN && stm7_stream->read() == SERIAL_NO_DATA);
    stm7_receive('X');
    stm7_stream->reset_read_buffer();
    CHECK(stm7_stream->get_rx_buffer_count() == 0 &&
          stm7_stream->get_rx_buffer_free() == RX_BUFFER_SIZE - 1);
    stm7_receive('Y');
    CHECK(stm7_stream->read() == 'Y');
    return 0;
}
