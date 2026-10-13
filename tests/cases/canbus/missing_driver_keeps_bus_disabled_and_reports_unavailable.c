#include "support/engine_host.h"
#include "canbus.h"
#include "check.h"

/* Weak board-driver link interface declared by its definitions in canbus.c. */
bool can_stop(void);
bool can_set_baud(uint32_t baud);
bool can_put(canbus_message_t message, bool extended);

int main(void)
{
    engine_prepare();
    canbus_init();
    setting_details_t *owner = NULL;
    CHECK(setting_get_details(Setting_CANbus_BaudRate, &owner) != NULL);
    CHECK(owner && owner->load);
    owner->load();
    CHECK(!canbus_enabled());
    CHECK(!can_stop());
    CHECK(!can_set_baud(250000));
    CHECK(!can_put((canbus_message_t){.id = 0x123, .len = 1, .data = {42}}, false));
    return EXIT_SUCCESS;
}
