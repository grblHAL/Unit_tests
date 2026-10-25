#include "stm7_serial_host.h"
int main(void)
{
    stm7_prepare();
    stm7_receive('!');
    stm7_receive('G');
    CHECK(stm7_rt_calls == 2 && stm7_stream->get_rx_buffer_count() == 1);
    CHECK(stm7_stream->read() == 'G' && stm7_stream->read() == SERIAL_NO_DATA);
    CHECK(stm7_stream->enqueue_rt_command('!') && !stm7_stream->enqueue_rt_command('X'));
    CHECK(stm7_rt_calls == 4 && stm7_stream->get_rx_buffer_count() == 0);
    return 0;
}
