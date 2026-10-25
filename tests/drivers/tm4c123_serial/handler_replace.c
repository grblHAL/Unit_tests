#include "uart_host.h"
static unsigned seen;
static bool custom(uint8_t value)
{
    seen++;
    return value == '?';
}
int main(void)
{
    uart_start();
    enqueue_realtime_command_ptr old = uart_stream->set_enqueue_rt_handler(custom);
    CHECK(old && uart_stream->set_enqueue_rt_handler(NULL) == custom);
    uart_receive('?');
    CHECK(seen == 1 && uart_stream->read() == SERIAL_NO_DATA);
    CHECK(uart_stream->enqueue_rt_command('?') && seen == 2);
    CHECK(uart_stream->set_enqueue_rt_handler(old) == custom);
    uart_receive('!');
    CHECK(rt_calls == 1 && uart_stream->read() == SERIAL_NO_DATA);
    return 0;
}
