#include "stm7_serial_host.h"
int main(void)
{
    stm7_triplex_prepare();
    CHECK(stream_connect(stm7_port_stream[2]));
    stm7_receive_port(2, 'G');
    stm7_receive_port(2, '1');
    CHECK(stm7_port_stream[2]->suspend_read(true));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending && hal.stream.read() == SERIAL_NO_DATA);
    stm7_receive_port(2, CMD_TOOL_ACK);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Active);
    stm7_receive_port(2, 'X');
    CHECK(hal.stream.read() == 'X');
    CHECK(stm7_port_stream[2]->suspend_read(false));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off && hal.stream.read() == 'G' &&
          hal.stream.read() == '1' && hal.stream.read() == SERIAL_NO_DATA);
    return 0;
}
