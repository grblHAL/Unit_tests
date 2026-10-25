#include "mpg_host.h"
#include "grbl/protocol.h"
static unsigned calls;
static bool filter(uint8_t value)
{
    calls++;
    return value == '!';
}
static void receive(uint8_t seq)
{
    const uint8_t data[] = {'G', '!'};
#if MPG_TRANSPORT_DEFAULT_TRANSPORT == 0
    (void)seq;
    mpg_bytes(data, sizeof(data));
#else
    mpg_receive(seq, MpgFrame_Dat, data, sizeof(data));
#endif
}
int main(void)
{
    mpg_start();
    enqueue_realtime_command_ptr original = proxy.set_enqueue_rt_handler(filter);
    CHECK(original == protocol_enqueue_realtime_command);
    CHECK(proxy.enqueue_rt_command('!') && !proxy.enqueue_rt_command('G'));
    CHECK(calls == 2 && proxy.get_rx_buffer_count() == 0);
    receive(1);
    CHECK(calls == 4 && rt_calls == 0 && proxy.read() == 'G' && proxy.read() == SERIAL_NO_DATA);
    CHECK(proxy.set_enqueue_rt_handler(NULL) == filter);
    CHECK(!proxy.enqueue_rt_command('!'));
    receive(2);
    CHECK(calls == 4 && proxy.get_rx_buffer_count() == 0);
    CHECK(mpg_command(NULL) == Status_OK && strstr(output, "rxovf=2"));
    CHECK(proxy.set_enqueue_rt_handler(original) == NULL);
    receive(3);
    CHECK(rt_calls == 2 && proxy.read() == 'G' && proxy.read() == SERIAL_NO_DATA);
    return 0;
}
