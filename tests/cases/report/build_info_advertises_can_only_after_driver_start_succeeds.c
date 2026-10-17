#include "support/build_report_host.h"
#include "canbus.h"
static bool start_succeeds;
static unsigned start_calls;
bool can_start(uint32_t baud, can_rx_enqueue_fn receive)
{
    CHECK(baud == 125000 && receive != NULL);
    start_calls++;
    return start_succeeds;
}
int main(void)
{
    prepare_build_report();
    canbus_init();
    setting_details_t *details = NULL;
    CHECK(setting_get_details(Setting_CANbus_BaudRate, &details) != NULL);
    CHECK(details != NULL && details->load != NULL);
    details->load();
    CHECK(start_calls == 1 && !canbus_enabled());
    build_report(true);
    CHECK(strstr(engine_output, ",CAN") == NULL);
    start_succeeds = true;
    details->load();
    CHECK(start_calls == 2 && canbus_enabled());
    engine_output[0] = 0;
    build_report(true);
    CHECK(strstr(engine_output, ",CAN") != NULL);
    return EXIT_SUCCESS;
}
