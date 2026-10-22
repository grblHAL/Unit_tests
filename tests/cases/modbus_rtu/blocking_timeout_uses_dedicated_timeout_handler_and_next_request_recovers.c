#include "support/rtu_blocking_host.h"
static unsigned timeouts;
static void timed_out(uint8_t code, void *context)
{
    CHECK(code == ModBus_Timeout && context == NULL); timeouts++;
}
static void service_two_timer_ticks(sys_state_t state)
{
    blocking_realtime(state);
    poll_rtu();
}
int main(void)
{
    prepare_rtu();
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {1, 3, 0, 0, 0, 1, 0, 0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed,
        .on_rx_timeout = timed_out};
    grbl.on_execute_realtime = service_two_timer_ticks;
    CHECK(!modbus_send(&message, &callbacks, true));
    CHECK(timeouts == 1 && exceptions == 0 && rx_calls == 0 && tx_calls == 1);
    reply_on_transmission = 2;
    CHECK(send_blocking_request(0));
    CHECK(tx_calls == 2 && rx_calls == 1 && exceptions == 0 && timeouts == 1);
    CHECK(reply.adu[3] == 0x12 && reply.adu[4] == 0x34);
    return EXIT_SUCCESS;
}
