#include "stm3_serial_host.h"
int main(void)
{
    stm3_prepare();
    CHECK(stream_connect(stm3_stream));
    stm3_receive('G');
    stm3_receive('1');
    CHECK(stm3_stream->suspend_read(true));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending && hal.stream.read() == SERIAL_NO_DATA);
    stm3_receive(CMD_TOOL_ACK);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Active);
    stm3_receive('X');
    CHECK(hal.stream.read() == 'X');
    CHECK(stm3_stream->suspend_read(false));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off && hal.stream.read() == 'G' &&
          hal.stream.read() == '1' && hal.stream.read() == SERIAL_NO_DATA);
    return 0;
}
