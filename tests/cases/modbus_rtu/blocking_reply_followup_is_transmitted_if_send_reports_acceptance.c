#include "support/rtu_blocking_host.h"
static bool followup_accepted;
static unsigned followup_attempts;
static void receive_and_request_next_register(modbus_message_t *message)
{
    received(message);
    modbus_message_t next = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {1,3,0,1,0,1,0,0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = received, .on_rx_exception = failed};
    followup_attempts++;
    followup_accepted = modbus_send(&next, &callbacks, false);
}
int main(void)
{
    prepare_rtu();
    reply_on_transmission = 1;
    grbl.on_execute_realtime = blocking_realtime;
    modbus_message_t first = {.tx_length = 8, .rx_length = 7, .crc_check = true,
        .adu = {1,3,0,0,0,1,0,0}};
    modbus_callbacks_t callbacks = {.on_rx_packet = receive_and_request_next_register,
        .on_rx_exception = failed};
    CHECK(modbus_send(&first, &callbacks, true));
    CHECK(followup_attempts == 1 && rx_calls == 1 && exceptions == 0);
    CHECK(reply.adu[3] == 0x12 && reply.adu[4] == 0x34);
    for(unsigned i = 0; i < 100; i++) poll_rtu();
    unsigned followup_transmissions = tx_calls - 1;
    if(followup_transmissions) {
        CHECK(followup_transmissions == 1 && tx_bytes[0] == 1 && tx_bytes[3] == 1);
        inject_reply(false);
        poll_rtu();
    }
    unsigned completed_before_retry = rx_calls, sent_before_retry = tx_calls;
    reply_on_transmission = tx_calls + 1;
    CHECK(send_blocking_request(0));
    CHECK(tx_calls == sent_before_retry + 1 && rx_calls == completed_before_retry + 1);
    CHECK(exceptions == 0 && followup_attempts == 1);
    CHECK(reply.adu[3] == 0x12 && reply.adu[4] == 0x34);
    fprintf(stderr, "Follow-up accepted=%u transmissions=%u; next independent request completed\n",
        followup_accepted, followup_transmissions);
    CHECK(!followup_accepted || (followup_transmissions == 1 && completed_before_retry == 2));
    return EXIT_SUCCESS;
}
