#include "telnet_host.h"
int main(void)
{
    telnet_connect();
    telnet_receive("G1X5\n", NULL);
    hal.stream.cancel_read_buffer();
    CHECK(hal.stream.read() == ASCII_CAN && hal.stream.read() == SERIAL_NO_DATA);
    telnet_receive("G0X0\n", NULL);
    hal.stream.reset_read_buffer();
    CHECK(hal.stream.read() == SERIAL_NO_DATA && tcp_frees == 2);
    telnet_receive("$I\n", NULL);
    CHECK(hal.stream.read() == '$' && hal.stream.read() == 'I' && hal.stream.read() == '\n');
    telnet_finish();
    return 0;
}
