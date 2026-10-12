#include "support/engine_host.h"
#include "canbus.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    canbus_message_t message = {.id = 0x123, .len = 1, .data = {42}};
    for(unsigned i = 0; i < 7; i++) CHECK(canbus_queue_tx(message, false));
    CHECK(!canbus_queue_tx(message, false));
    return EXIT_SUCCESS;
}
