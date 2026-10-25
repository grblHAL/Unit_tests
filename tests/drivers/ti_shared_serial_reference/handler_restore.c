#include "reference_host.h"
static unsigned calls;
static bool custom(char value)
{
    calls++;
    return value == '?';
}
int main(void)
{
    uart_start();
    enqueue_realtime_command_ptr old = uart_stream->set_enqueue_rt_handler(custom);
    CHECK(old == protocol_enqueue_realtime_command);
    CHECK(uart_stream->enqueue_rt_command('?') && !uart_stream->enqueue_rt_command('G'));
    CHECK(calls == 2 && uart_stream->get_rx_buffer_count() == 0);
    uart_receive('?');
    uart_receive('G');
    CHECK(calls == 4 && uart_stream->get_rx_buffer_count() == 1);
    CHECK(uart_stream->set_enqueue_rt_handler(old) == custom);
    uart_receive('!');
    CHECK(rt_calls == 1 && calls == 4 && uart_stream->read() == 'G' &&
          uart_stream->read() == SERIAL_NO_DATA);
    return 0;
}
