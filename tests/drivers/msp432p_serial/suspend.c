#include "msp_host.h"
int main(void)
{
    msp_start();
    CHECK(stream_connect(msp_stream));
    msp_receive('G');
    msp_receive('1');
    CHECK(msp_stream->suspend_read(true));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending && hal.stream.read() == SERIAL_NO_DATA);
    msp_receive(CMD_TOOL_ACK);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Active);
    msp_receive('X');
    CHECK(hal.stream.read() == 'X');
    CHECK(msp_stream->suspend_read(false));
    CHECK(hal.stream.read() == 'G' && hal.stream.read() == '1' &&
          hal.stream.read() == SERIAL_NO_DATA);
    return 0;
}
