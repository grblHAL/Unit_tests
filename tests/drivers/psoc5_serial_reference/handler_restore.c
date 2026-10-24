#include "psoc_host.h"
static unsigned calls;
static bool custom(char value)
{
    calls++;
    return value == '?';
}
int main(void)
{
    psoc_start();
    enqueue_realtime_command_ptr old = psoc_stream->set_enqueue_rt_handler(custom);
    CHECK(old == protocol_enqueue_realtime_command);
    CHECK(psoc_stream->enqueue_rt_command('?') && !psoc_stream->enqueue_rt_command('G'));
    CHECK(calls == 2 && psoc_stream->get_rx_buffer_count() == 0);
    const uint8_t input[] = {'?', 'G'};
    psoc_receive(input, sizeof(input));
    CHECK(calls == 4 && psoc_stream->get_rx_buffer_count() == 1);
    CHECK(psoc_stream->set_enqueue_rt_handler(old) == custom);
    const uint8_t hold = '!';
    psoc_receive(&hold, 1);
    CHECK(rt_calls == 1 && calls == 4 && psoc_stream->read() == 'G' &&
          psoc_stream->read() == SERIAL_NO_DATA);
    return 0;
}
