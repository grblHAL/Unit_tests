#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_triplex_prepare();
    CHECK(stream_connect(stmh7_port_stream[1]));
    stmh7_receive_port(1, 'G');
    stmh7_receive_port(1, '1');
    stmh7_receive_port(2, 'M');
    stmh7_receive_port(2, '2');
    CHECK(stmh7_port_stream[1]->suspend_read(true));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending && hal.stream.read() == SERIAL_NO_DATA);
    stmh7_port_stream[2]->cancel_read_buffer();
    CHECK(stmh7_port_stream[2]->read() == ASCII_CAN &&
          stmh7_port_stream[2]->read() == SERIAL_NO_DATA);
    stmh7_receive_port(1, CMD_TOOL_ACK);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Active);
    stmh7_receive_port(1, 'X');
    CHECK(hal.stream.read() == 'X');
    CHECK(stmh7_port_stream[1]->suspend_read(false));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off && hal.stream.read() == 'G' &&
          hal.stream.read() == '1' && hal.stream.read() == SERIAL_NO_DATA);
    stmh7_receive_port(2, 'Y');
    CHECK(stmh7_port_stream[2]->read() == 'Y');
    return 0;
}
