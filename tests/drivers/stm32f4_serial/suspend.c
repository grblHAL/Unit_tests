#include "stm_serial_host.h"
int main(void)
{
    stm_serial_prepare();
    CHECK(stream_connect(stm_stream));
    stm_receive('G');
    stm_receive('1');
    CHECK(stm_stream->suspend_read(true));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending && hal.stream.read() == SERIAL_NO_DATA);
    stm_receive(CMD_TOOL_ACK);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Active);
    stm_receive('X');
    CHECK(hal.stream.read() == 'X');
    CHECK(stm_stream->suspend_read(false));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off && hal.stream.read() == 'G' &&
          hal.stream.read() == '1' && hal.stream.read() == SERIAL_NO_DATA);
    return 0;
}
