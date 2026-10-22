#include "support/rtu_blocking_host.h"

static uint8_t partial_header[] = {1, 0x83};
static unsigned partial_attempt, partial_ticks;
static bool partial_injected;
static void service_partial_reply(sys_state_t state)
{
    (void)state;
    CHECK(++realtime_calls < 2000);
    poll_rtu();
    if(partial_attempt != tx_calls) {
        partial_attempt = tx_calls;
        partial_ticks = 0;
        partial_injected = false;
    }
    if(tx_calls && ++partial_ticks >= 2 && !partial_injected) {
        memcpy(rx_bytes, partial_header, sizeof(partial_header));
        rx_position = 0;
        rx_length = sizeof(partial_header);
        partial_injected = true;
    }
}
int main(void)
{
    prepare_rtu();
    modbus_message_t message = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {1, 3, 0, 0, 0, 1, 0, 0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    grbl.on_execute_realtime = service_partial_reply;
    CHECK(!modbus_send(&message, &callbacks, true));
    CHECK(partial_injected && tx_calls == 1 && rx_calls == 0 && exceptions == 1);
    CHECK(exception_code == ModBus_UnknownException);
    partial_header[1] = 3;
    CHECK(!modbus_send(&message, &callbacks, true));
    CHECK(tx_calls == 2 && rx_calls == 0 && exceptions == 2 && exception_code == ModBus_Timeout);
    partial_header[0] = 2;
    partial_header[1] = 0x83;
    CHECK(!modbus_send(&message, &callbacks, true));
    CHECK(tx_calls == 3 && rx_calls == 0 && exceptions == 3 && exception_code == ModBus_Timeout);
    reply_on_transmission = 4;
    CHECK(send_blocking_request(0));
    CHECK(tx_calls == 4 && rx_calls == 1 && exceptions == 3);
    CHECK(reply.adu[3] == 0x12 && reply.adu[4] == 0x34);
    for(unsigned tick = 0; tick < 20; tick++) poll_rtu();
    CHECK(!modbus_isbusy() && engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
