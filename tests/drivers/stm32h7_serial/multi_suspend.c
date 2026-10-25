#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_triplex_prepare();
    CHECK(stream_connect(stmh7_port_stream[2]));
    stmh7_receive_port(2, 'G');
    stmh7_receive_port(2, '1');
    CHECK(stmh7_port_stream[2]->suspend_read(true));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending && hal.stream.read() == SERIAL_NO_DATA);
    stmh7_receive_port(2, CMD_TOOL_ACK);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Active);
    stmh7_receive_port(2, 'X');
    CHECK(hal.stream.read() == 'X');
    CHECK(stmh7_port_stream[2]->suspend_read(false));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off && hal.stream.read() == 'G' &&
          hal.stream.read() == '1' && hal.stream.read() == SERIAL_NO_DATA);
    return 0;
}
