#include "stm_serial_host.h"
int main(void)
{
    stm_serial_prepare();
    stm_receive('G');
    stm_receive('1');
    stm_stream->cancel_read_buffer();
    CHECK(stm_stream->read() == ASCII_CAN && stm_stream->read() == SERIAL_NO_DATA);
    stm_receive('X');
    stm_stream->reset_read_buffer();
    CHECK(stm_stream->get_rx_buffer_count() == 0 &&
          stm_stream->get_rx_buffer_free() == RX_BUFFER_SIZE - 1);
    stm_receive('Y');
    CHECK(stm_stream->read() == 'Y');
    return 0;
}
