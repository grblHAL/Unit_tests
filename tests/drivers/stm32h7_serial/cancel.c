#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_prepare();
    stmh7_receive('G');
    stmh7_receive('1');
    stmh7_stream->cancel_read_buffer();
    CHECK(stmh7_stream->read() == ASCII_CAN && stmh7_stream->read() == SERIAL_NO_DATA);
    stmh7_receive('X');
    stmh7_stream->reset_read_buffer();
    CHECK(stmh7_stream->get_rx_buffer_count() == 0 &&
          stmh7_stream->get_rx_buffer_free() == RX_BUFFER_SIZE - 1);
    stmh7_receive('Y');
    CHECK(stmh7_stream->read() == 'Y');
    return 0;
}
