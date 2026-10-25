#include "sam_host.h"
int main(void)
{
    sam_prepare();
    CHECK(stream_connect(sam_stream[0]));
    sam_receive(0, 'G');
    sam_receive(0, '1');
    CHECK(sam_stream[0]->suspend_read(true));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending && hal.stream.read() == SERIAL_NO_DATA);
    sam_receive(0, CMD_TOOL_ACK);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Active);
    sam_receive(0, 'X');
    CHECK(hal.stream.read() == 'X');
    CHECK(sam_stream[0]->suspend_read(false));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off && hal.stream.read() == 'G' &&
          hal.stream.read() == '1' && hal.stream.read() == SERIAL_NO_DATA);
    return 0;
}
