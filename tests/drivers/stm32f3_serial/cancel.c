#include "stm3_serial_host.h"
int main(void)
{
    stm3_prepare();
    stm3_receive('G');
    stm3_receive('1');
    stm3_stream->cancel_read_buffer();
    CHECK(stm3_stream->read() == ASCII_CAN && stm3_stream->read() == SERIAL_NO_DATA);
    stm3_receive('X');
    stm3_stream->reset_read_buffer();
    CHECK(stm3_stream->read() == SERIAL_NO_DATA);
    stm3_receive('Y');
    CHECK(stm3_stream->read() == 'Y');
    return 0;
}
