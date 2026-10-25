#include "at_host.h"
static unsigned intercepted;
static bool handler(uint8_t c)
{
    if (c == '!')
    {
        intercepted++;
        return true;
    }
    return false;
}
int main(void)
{
    at_prepare();
    at_load(WiFiMode_STA);
    at_start();
    at_connect();
    CHECK(hal.stream.read() == ASCII_CAN);
    enqueue_realtime_command_ptr previous = hal.stream.set_enqueue_rt_handler(handler);
    CHECK(previous && hal.stream.set_enqueue_rt_handler(NULL) == handler);
    CHECK(at_uart_handler('!') && at_uart_handler('G') && at_uart_handler('\n'));
    CHECK(intercepted == 1 && hal.stream.read() == 'G' && hal.stream.read() == '\n');
    CHECK(hal.stream.read() == SERIAL_NO_DATA && hal.stream.enqueue_rt_command('!') &&
          intercepted == 2);
    CHECK(hal.stream.set_enqueue_rt_handler(previous) == handler);
    return 0;
}
