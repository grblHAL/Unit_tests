#include "sam_host.h"
static unsigned counts[2];
static bool first(uint8_t c)
{
    CHECK(c == 0x85);
    counts[0]++;
    return true;
}
static bool second(uint8_t c)
{
    CHECK(c == 0x86);
    counts[1]++;
    return true;
}
int main(void)
{
    sam_prepare();
    enqueue_realtime_command_ptr old0 = sam_stream[0]->set_enqueue_rt_handler(first),
                                 old1 = sam_stream[1]->set_enqueue_rt_handler(second);
    sam_receive(0, 0x85);
    sam_receive(1, 0x86);
    CHECK(counts[0] == 1 && counts[1] == 1 && !sam_stream[0]->get_rx_buffer_count() &&
          !sam_stream[1]->get_rx_buffer_count());
    CHECK(sam_stream[0]->set_enqueue_rt_handler(old0) == first &&
          sam_stream[1]->set_enqueue_rt_handler(old1) == second);
    sam_receive(0, '!');
    sam_receive(1, '!');
    CHECK(!sam_stream[0]->get_rx_buffer_count() && !sam_stream[1]->get_rx_buffer_count());
    return 0;
}
