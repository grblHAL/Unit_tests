#include "stm_serial_host.h"
int main(void)
{
    stm_serial_prepare();
    stm_receive('!');
    stm_receive('G');
    CHECK(stm_rt_calls == 2 && stm_stream->get_rx_buffer_count() == 1);
    CHECK(stm_stream->read() == 'G' && stm_stream->read() == SERIAL_NO_DATA);
    CHECK(stm_stream->enqueue_rt_command('!') && !stm_stream->enqueue_rt_command('X'));
    CHECK(stm_rt_calls == 4 && stm_stream->get_rx_buffer_count() == 0);
    return 0;
}
