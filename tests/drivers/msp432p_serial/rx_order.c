#include "msp_host.h"
int main(void)
{
    msp_start();
    msp_receive('G');
    msp_receive('1');
    msp_receive('!');
    msp_receive('X');
    CHECK(rt_calls == 4 && msp_stream->get_rx_buffer_free() == 28);
    CHECK(msp_stream->read() == 'G' && msp_stream->read() == '1' && msp_stream->read() == 'X' &&
          msp_stream->read() == SERIAL_NO_DATA);
    CHECK(cpu_enabled && irq_disables == 4);
    return 0;
}
