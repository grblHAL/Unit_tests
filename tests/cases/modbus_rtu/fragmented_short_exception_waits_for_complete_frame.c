#include "support/rtu_short_exception_host.h"

int main(void)
{
    start_short_exception_request();
    uint8_t frame[5];
    make_short_exception(frame);
    append_short_reply(frame, 2);
    for(unsigned tick = 0; tick < 3; tick++) poll_rtu();
    CHECK(short_rx_calls == 0 && short_exceptions == 0 && short_timeouts == 0);
    append_short_reply(frame + 2, 2);
    for(unsigned tick = 0; tick < 3; tick++) poll_rtu();
    CHECK(short_rx_calls == 0 && short_exceptions == 0 && short_timeouts == 0);
    append_short_reply(frame + 4, 1);
    finish_short_exception(ModBus_IllegalDataAddress);
    return EXIT_SUCCESS;
}
