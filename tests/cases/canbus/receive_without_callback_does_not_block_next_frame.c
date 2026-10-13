#include "support/can_host.h"

static unsigned calls;
static bool received(canbus_message_t frame)
{
    CHECK(frame.id == 0x200 && frame.data[0] == 42);
    calls++;
    return true;
}
int main(void)
{
    prepare_can();
    canbus_message_t frame = {.id = 0x200, .len = 1, .data = {42}};
    CHECK(can_receive(frame, NULL));
    CHECK(can_receive(frame, received));
    poll_can();
    CHECK(calls == 0);
    poll_can();
    CHECK(calls == 1);
    poll_can();
    CHECK(calls == 1);
    return EXIT_SUCCESS;
}
