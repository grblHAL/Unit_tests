#include "support/engine_host.h"
#include "canbus.h"
#include "check.h"
static can_rx_enqueue_fn receive;
static uint32_t baud_seen;
static bool start_result = true;
bool can_start(uint32_t baud, can_rx_enqueue_fn callback)
{
    baud_seen = baud;
    receive = callback;
    return start_result;
}
static void load_bus(void)
{
    setting_details_t *details = NULL;
    canbus_init();
    CHECK(setting_get_details(Setting_CANbus_BaudRate, &details) != NULL);
    CHECK(details != NULL && details->load != NULL);
    details->load();
    CHECK(receive != NULL);
    CHECK(baud_seen >= 125000);
}

int main(void)
{
    engine_prepare();
    settings.canbus_baud = 3;
    load_bus();
    CHECK(canbus_enabled());
    CHECK(baud_seen == 1000000);
    return EXIT_SUCCESS;
}
