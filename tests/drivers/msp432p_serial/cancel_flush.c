#include "msp_host.h"
int main(void)
{
    msp_start();
    msp_receive('G');
    msp_stream->cancel_read_buffer();
    CHECK(msp_stream->read() == ASCII_CAN && msp_stream->read() == SERIAL_NO_DATA);
    msp_receive('X');
    msp_stream->reset_read_buffer();
    CHECK(msp_stream->read() == SERIAL_NO_DATA && msp_stream->get_rx_buffer_free() == 31);
    return 0;
}
