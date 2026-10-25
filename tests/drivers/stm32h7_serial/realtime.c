#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_prepare();
    stmh7_receive('!');
    stmh7_receive('G');
    CHECK(stmh7_rt_calls == 2 && stmh7_stream->get_rx_buffer_count() == 1);
    CHECK(stmh7_stream->read() == 'G' && stmh7_stream->read() == SERIAL_NO_DATA);
    CHECK(stmh7_stream->enqueue_rt_command('!') && !stmh7_stream->enqueue_rt_command('X'));
    CHECK(stmh7_rt_calls == 4 && stmh7_stream->get_rx_buffer_count() == 0);
    return 0;
}
