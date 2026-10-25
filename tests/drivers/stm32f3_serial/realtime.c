#include "stm3_serial_host.h"
int main(void)
{
    stm3_prepare();
    stm3_receive('!');
    stm3_receive('G');
    CHECK(stm3_rt_calls == 2 && stm3_stream->read() == 'G' &&
          stm3_stream->read() == SERIAL_NO_DATA);
    CHECK(stm3_stream->enqueue_rt_command('!') && !stm3_stream->enqueue_rt_command('X'));
    CHECK(stm3_rt_calls == 4);
    return 0;
}
