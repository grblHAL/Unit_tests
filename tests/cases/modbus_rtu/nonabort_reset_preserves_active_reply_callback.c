#include "support/rtu_host.h"
static unsigned resets;
static void original_reset(void) { resets++; }

int main(void)
{
    prepare_rtu_with_reset(original_reset);
    send_request();
    hal.driver_reset();
    CHECK(resets == 1);
    inject_reply(false);
    poll_rtu();
    CHECK(tx_calls == 1 && rx_calls == 1 && exceptions == 0);
    return EXIT_SUCCESS;
}
