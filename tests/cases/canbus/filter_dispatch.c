#include "support/engine_host.h"
#include "canbus.h"
#include "check.h"
static uint32_t id_seen, mask_seen;
static bool extended_seen;
bool can_add_filter(uint32_t id, uint32_t mask, bool extended, can_rx_ptr callback)
{
    CHECK(callback == NULL);
    id_seen = id; mask_seen = mask; extended_seen = extended;
    return true;
}
int main(void)
{
    engine_prepare();
    CHECK(canbus_add_filter(0x12345, 0x1fffffff, true, NULL));
    CHECK(id_seen == 0x12345);
    CHECK(mask_seen == 0x1fffffff);
    CHECK(extended_seen);
    return EXIT_SUCCESS;
}
