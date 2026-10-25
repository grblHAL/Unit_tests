#include "stm_serial_host.h"
#include "grbl/protocol.h"
static unsigned calls[3];
static bool first(uint8_t value)
{
    calls[0]++;
    return value == '!';
}
static bool second(uint8_t value)
{
    calls[1]++;
    return value == '?';
}
static bool third(uint8_t value)
{
    calls[2]++;
    return value == '~';
}
int main(void)
{
    stm_triplex_prepare();
    enqueue_realtime_command_ptr handlers[] = {first, second, third};
    const uint8_t command[] = {'!', '?', '~'};
    for (unsigned n = 0; n < 3; n++)
    {
        CHECK(stm_port_stream[n]->set_enqueue_rt_handler(handlers[n]) ==
              protocol_enqueue_realtime_command);
        CHECK(stm_port_stream[n]->enqueue_rt_command(command[n]));
        stm_receive_port(n, command[n]);
        stm_receive_port(n, 'A' + n);
        CHECK(calls[n] == 3 && stm_port_stream[n]->read() == 'A' + (int)n);
        CHECK(stm_port_stream[n]->read() == SERIAL_NO_DATA);
    }
    CHECK(calls[0] == 3 && calls[1] == 3 && calls[2] == 3 && stm_rt_calls == 0);
    for (unsigned n = 0; n < 3; n++)
        CHECK(stm_port_stream[n]->set_enqueue_rt_handler(protocol_enqueue_realtime_command) ==
              handlers[n]);
    return 0;
}
