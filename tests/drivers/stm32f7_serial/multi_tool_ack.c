#include "stm7_serial_host.h"
int main(void)
{
    stm7_triplex_prepare();
    CHECK(stream_connect(stm7_port_stream[1]));
    stm7_receive_port(1, 'G');
    stm7_receive_port(1, '1');
    stm7_receive_port(2, 'M');
    stm7_receive_port(2, '2');
    CHECK(stm7_port_stream[1]->suspend_read(true));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Pending && hal.stream.read() == SERIAL_NO_DATA);
    stm7_port_stream[2]->cancel_read_buffer();
    CHECK(stm7_port_stream[2]->read() == ASCII_CAN &&
          stm7_port_stream[2]->read() == SERIAL_NO_DATA);
    stm7_receive_port(1, CMD_TOOL_ACK);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Active);
    stm7_receive_port(1, 'X');
    CHECK(hal.stream.read() == 'X');
    CHECK(stm7_port_stream[1]->suspend_read(false));
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off && hal.stream.read() == 'G' &&
          hal.stream.read() == '1' && hal.stream.read() == SERIAL_NO_DATA);
    stm7_receive_port(2, 'Y');
    CHECK(stm7_port_stream[2]->read() == 'Y');
    return 0;
}
