#include "support/can_host.h"
#include "check.h"
static unsigned rx_calls;
static bool received(canbus_message_t message)
{
    CHECK(message.id == 0x123 && message.len == 1 && message.data[0] == 42);
    rx_calls++;
    return true;
}
int main(void)
{
    prepare_can();
    canbus_message_t frame = {.id = 0x123, .len = 1, .data = {42}};
    CHECK(can_receive(frame, received));
    CHECK(rx_calls == 0);
    poll_can();
    CHECK(rx_calls == 1);
    poll_can();
    CHECK(rx_calls == 1);
    return EXIT_SUCCESS;
}
