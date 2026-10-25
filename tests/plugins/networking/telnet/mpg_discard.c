#include "telnet_host.h"
int main(void)
{
    telnet_connect();
    hal.stream.state.is_mpg = true;
    telnet_receive("G1X5!\n", NULL);
    CHECK(tcp_acks == 6 && tcp_frees == 1 && rt_calls == 0 && hal.stream.read() == SERIAL_NO_DATA);
    hal.stream.state.is_mpg = false;
    telnet_receive("$I\n", NULL);
    CHECK(rt_calls == 3 && hal.stream.read() == '$');
    telnet_finish();
    return 0;
}
