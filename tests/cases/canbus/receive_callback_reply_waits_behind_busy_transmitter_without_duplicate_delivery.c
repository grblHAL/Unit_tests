#include "support/can_host.h"
static unsigned received;
static bool reply_to_request(canbus_message_t message)
{
    CHECK(message.id == 0x222 && message.len == 2);
    CHECK(message.data[0] == 0x37 && message.data[1] == 0x48);
    received++;
    message.id = 0x223;
    CHECK(canbus_queue_tx(message, false));
    return true;
}
int main(void)
{
    prepare_can();
    canbus_message_t original = {.id = 0x101, .len = 1, .data = {0x55}};
    canbus_message_t request = {.id = 0x222, .len = 2, .data = {0x37, 0x48}};
    CHECK(canbus_queue_tx(original, true));
    CHECK(can_receive(request, reply_to_request));
    tx_ready = false;
    for(unsigned i = 1; i <= 2; i++) {
        poll_can();
        CHECK(tx_calls == i && tx_frame.id == original.id && tx_extended);
        CHECK(tx_frame.data[0] == 0x55 && received == 1);
    }
    tx_ready = true;
    poll_can();
    CHECK(tx_calls == 3 && tx_frame.id == original.id && tx_extended);
    poll_can();
    CHECK(tx_calls == 4 && tx_frame.id == 0x223 && !tx_extended);
    CHECK(tx_frame.len == 2 && tx_frame.data[0] == 0x37 && tx_frame.data[1] == 0x48);
    poll_can();
    CHECK(tx_calls == 4 && received == 1);
    return EXIT_SUCCESS;
}
