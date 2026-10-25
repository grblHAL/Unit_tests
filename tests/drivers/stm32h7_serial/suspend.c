#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_prepare();
    CHECK(stream_connect(stmh7_stream));
    stmh7_receive('G');
    stmh7_receive('1');
    CHECK(stmh7_stream->suspend_read(true));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending && hal.stream.read() == SERIAL_NO_DATA);
    stmh7_receive(CMD_TOOL_ACK);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Active);
    stmh7_receive('X');
    CHECK(hal.stream.read() == 'X');
    CHECK(stmh7_stream->suspend_read(false));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off && hal.stream.read() == 'G' &&
          hal.stream.read() == '1' && hal.stream.read() == SERIAL_NO_DATA);
    return 0;
}
