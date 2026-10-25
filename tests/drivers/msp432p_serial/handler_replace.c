#include "msp_host.h"
static unsigned seen;
static bool custom(uint8_t value)
{
    seen++;
    return value == '~';
}
int main(void)
{
    msp_start();
    enqueue_realtime_command_ptr old = msp_stream->set_enqueue_rt_handler(custom);
    CHECK(old && msp_stream->set_enqueue_rt_handler(NULL) == custom);
    msp_receive('~');
    CHECK(seen == 1 && msp_stream->read() == SERIAL_NO_DATA);
    CHECK(msp_stream->enqueue_rt_command('~') && seen == 2);
    CHECK(msp_stream->set_enqueue_rt_handler(old) == custom);
    msp_receive('!');
    CHECK(rt_calls == 1 && msp_stream->read() == SERIAL_NO_DATA);
    return 0;
}
