#include "support/rtu_host.h"
#include "check.h"
static bool inside_stream_poll;
static void blocking_foreground(sys_state_t state)
{
    (void)state;
    if(inside_stream_poll) {
        CHECK(modbus_isbusy());
        CHECK(tx_calls == 1 && rx_calls == 0 && exceptions == 0);
    }
}

int main(void)
{
    prepare_rtu();
    grbl.on_execute_realtime = blocking_foreground;
    send_request();
    CHECK(modbus_isbusy());
    inside_stream_poll = true;
    CHECK(stream_tx_blocking());
    inside_stream_poll = false;
    CHECK(modbus_isbusy());
    CHECK(tx_calls == 1 && rx_calls == 0 && exceptions == 0);
    inject_reply(false);
    poll_rtu();
    CHECK(tx_calls == 1 && rx_calls == 1 && exceptions == 0);
    return EXIT_SUCCESS;
}
