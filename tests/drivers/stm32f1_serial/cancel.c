#include "stm1_serial_host.h"
int main(void)
{
    stm1_prepare();
    stm1_receive('G');
    stm1_receive('1');
    stm1_stream->cancel_read_buffer();
    CHECK(stm1_stream->read() == ASCII_CAN && stm1_stream->read() == SERIAL_NO_DATA);
    stm1_receive('X');
    stm1_stream->reset_read_buffer();
    CHECK(stm1_stream->read() == SERIAL_NO_DATA);
    stm1_receive('Y');
    CHECK(stm1_stream->read() == 'Y');
    return 0;
}
