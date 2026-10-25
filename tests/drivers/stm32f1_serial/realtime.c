#include "stm1_serial_host.h"
int main(void)
{
    stm1_prepare();
    stm1_receive('!');
    stm1_receive('G');
    CHECK(stm1_rt_calls == 2 && stm1_stream->read() == 'G' &&
          stm1_stream->read() == SERIAL_NO_DATA);
    CHECK(stm1_stream->enqueue_rt_command('!') && !stm1_stream->enqueue_rt_command('X'));
    CHECK(stm1_rt_calls == 4);
    return 0;
}
