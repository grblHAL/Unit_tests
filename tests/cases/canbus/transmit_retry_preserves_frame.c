#include "support/can_host.h"
#include "check.h"

int main(void)
{
    prepare_can();
    canbus_message_t frame = {.id = 0x123, .len = 1, .data = {42}};
    CHECK(canbus_queue_tx(frame, true));
    tx_ready = false;
    poll_can();
    CHECK(tx_calls == 1 && tx_frame.id == frame.id);
    tx_ready = true;
    poll_can();
    CHECK(tx_calls == 2 && tx_frame.id == frame.id && tx_extended);
    poll_can();
    CHECK(tx_calls == 2);
    return EXIT_SUCCESS;
}
