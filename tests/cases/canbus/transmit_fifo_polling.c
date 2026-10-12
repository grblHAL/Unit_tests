#include "support/can_host.h"
#include "check.h"

int main(void)
{
    prepare_can();
    canbus_message_t first = {.id = 0x123, .len = 1, .data = {42}};
    canbus_message_t second = {.id = 0x456, .len = 1, .data = {99}};
    CHECK(canbus_queue_tx(first, false));
    CHECK(canbus_queue_tx(second, true));
    poll_can();
    CHECK(tx_calls == 1 && tx_frame.id == first.id && tx_frame.data[0] == 42);
    CHECK(!tx_extended);
    poll_can();
    CHECK(tx_calls == 2 && tx_frame.id == second.id && tx_frame.data[0] == 99);
    CHECK(tx_extended);
    poll_can();
    CHECK(tx_calls == 2);
    return EXIT_SUCCESS;
}
