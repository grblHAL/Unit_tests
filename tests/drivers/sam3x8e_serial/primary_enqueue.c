#include "sam_host.h"
static unsigned calls;
static uint8_t last;
static bool handler(uint8_t value)
{
    calls++;
    last = value;
    return value == 0x85;
}
int main(void)
{
    sam_prepare();
    enqueue_realtime_command_ptr old = sam_stream[0]->set_enqueue_rt_handler(handler);
    CHECK(old == protocol_enqueue_realtime_command);
    CHECK(sam_stream[0]->enqueue_rt_command(0x85) && calls == 1 && last == 0x85);
    CHECK(!sam_stream[0]->enqueue_rt_command('G') && calls == 2 && last == 'G');
    CHECK(sam_stream[0]->get_rx_buffer_count() == 0);
    sam_receive(0, 0x85);
    CHECK(calls == 3 && sam_stream[0]->get_rx_buffer_count() == 0);
    CHECK(sam_stream[0]->set_enqueue_rt_handler(old) == handler);
    CHECK(sam_stream[0]->enqueue_rt_command('!') && !sam_stream[0]->enqueue_rt_command('G') &&
          calls == 3);
    sam_receive(0, 'G');
    CHECK(sam_stream[0]->read() == 'G' && sam_stream[0]->read() == SERIAL_NO_DATA);
    CHECK(sam_stream[1]->get_rx_buffer_count() == 0);
    return 0;
}
