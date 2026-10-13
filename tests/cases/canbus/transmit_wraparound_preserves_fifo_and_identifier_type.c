#include "support/can_host.h"

int main(void)
{
    prepare_can();
    for(unsigned batch = 0; batch < 5; batch++) {
        for(unsigned slot = 0; slot < 7; slot++) {
            unsigned id = batch * 7 + slot;
            canbus_message_t frame = {.id = 0x100 + id, .len = 1, .data = {(uint8_t)id}};
            CHECK(canbus_queue_tx(frame, (id % 2) != 0));
        }
        for(unsigned slot = 0; slot < 7; slot++) {
            unsigned id = batch * 7 + slot;
            poll_can();
            CHECK(tx_calls == id + 1 && tx_frame.id == 0x100 + id);
            CHECK(tx_frame.len == 1 && tx_frame.data[0] == id);
            CHECK(tx_extended == ((id % 2) != 0));
        }
    }
    poll_can();
    CHECK(tx_calls == 35);
    return EXIT_SUCCESS;
}
