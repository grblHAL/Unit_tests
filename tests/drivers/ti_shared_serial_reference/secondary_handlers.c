#include "reference_host.h"
static unsigned first_calls, second_calls;
static bool first(char c)
{
    first_calls++;
    return c == '!';
}
static bool second(char c)
{
    second_calls++;
    return c == '?';
}
int main(void)
{
    uart_start();
    uart2_start();
    CHECK(uart2_stream->disable_rx(false));
    enqueue_realtime_command_ptr old0 = uart_stream->set_enqueue_rt_handler(first),
                                 old1 = uart2_stream->set_enqueue_rt_handler(second);
    CHECK(uart_stream->enqueue_rt_command('!') && uart2_stream->enqueue_rt_command('?'));
    uart_receive('?');
    uart2_event(UART_INT_RX, '!');
    CHECK(first_calls == 2 && second_calls == 2 && uart_stream->read() == '?' &&
          uart2_stream->read() == '!');
    CHECK(uart_stream->set_enqueue_rt_handler(old0) == first &&
          uart2_stream->set_enqueue_rt_handler(old1) == second);
    uart_receive('!');
    uart2_event(UART_INT_RX, '!');
    CHECK(rt_calls == 2 && uart_stream->read() == SERIAL_NO_DATA &&
          uart2_stream->read() == SERIAL_NO_DATA);
    return 0;
}
