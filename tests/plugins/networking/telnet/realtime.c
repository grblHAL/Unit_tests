#include "telnet_host.h"
int main(void)
{
    telnet_connect();
    telnet_receive("G1!", "X1\n");
    CHECK(rt_calls == 6 && tcp_acks == 6 && tcp_frees == 1);
    const char *expected = "G1X1\n";
    for (const char *s = expected; *s; s++)
        CHECK(hal.stream.read() == *s);
    CHECK(hal.stream.read() == SERIAL_NO_DATA);
    CHECK(hal.stream.enqueue_rt_command('!') && !hal.stream.enqueue_rt_command('G'));
    telnet_finish();
    return 0;
}
