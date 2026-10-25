#include "support/rtu_host.h"

int main(void)
{
    prepare_rtu();
    pending_tx_bytes = 3;
    send_request();
    for(unsigned pending = 3; pending > 0; pending--) {
        pending_tx_bytes = (uint16_t)pending;
        poll_rtu();
        CHECK(modbus_isbusy());
        CHECK(tx_calls == 1 && rx_calls == 0 && exceptions == 0);
    }
    pending_tx_bytes = 0;
    poll_rtu();
    inject_reply(false);
    poll_rtu();
    CHECK(tx_calls == 1 && rx_calls == 1 && exceptions == 0);
    CHECK(reply.rx_length == 7 && reply.adu[3] == 0x12 && reply.adu[4] == 0x34);
    for(unsigned tick = 0; tick < 50 && modbus_isbusy(); tick++) poll_rtu();
    CHECK(!modbus_isbusy());
    return EXIT_SUCCESS;
}
