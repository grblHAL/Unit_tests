#include "stm1_serial_host.h"
int main(void)
{
    stm1_prepare();
    CHECK(stream_connect(stm1_stream));
    stm1_receive('G');
    stm1_receive('1');
    CHECK(stm1_stream->suspend_read(true));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending && hal.stream.read() == SERIAL_NO_DATA);
    stm1_receive(CMD_TOOL_ACK);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Active);
    stm1_receive('X');
    CHECK(hal.stream.read() == 'X');
    CHECK(stm1_stream->suspend_read(false));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off && hal.stream.read() == 'G' &&
          hal.stream.read() == '1' && hal.stream.read() == SERIAL_NO_DATA);
    return 0;
}
