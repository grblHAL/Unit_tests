#include "support/can_host.h"
static unsigned received;
static bool accept_frame(canbus_message_t message)
{
    CHECK(message.id == 0x123 + received);
    CHECK(message.len == 1 && message.data[0] == received);
    received++;
    return true;
}
int main(void)
{
    prepare_can();
    for(unsigned i = 0; i < 7; i++) {
        canbus_message_t message = {.id = 0x123 + i, .len = 1, .data = {i}};
        CHECK(can_receive(message, accept_frame));
    }
    canbus_message_t retry = {.id = 0x12a, .len = 1, .data = {7}};
    CHECK(!can_receive(retry, accept_frame));
    CHECK(received == 0);
    poll_can();
    CHECK(received == 1);
    CHECK(can_receive(retry, accept_frame));
    for(unsigned i = 0; i < 7; i++) poll_can();
    CHECK(received == 8);
    poll_can();
    CHECK(received == 8 && tx_calls == 0);
    return EXIT_SUCCESS;
}
