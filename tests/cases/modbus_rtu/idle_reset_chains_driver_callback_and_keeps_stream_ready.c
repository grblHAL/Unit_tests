#include "support/rtu_host.h"
static unsigned resets;
static void original_reset(void) { resets++; }

int main(void)
{
    prepare_rtu_with_reset(original_reset);
    reset_rtu_driver();
    CHECK(resets == 1 && modbus_isup().rtu);
    send_request();
    inject_reply(false);
    poll_rtu();
    CHECK(rx_calls == 1 && exceptions == 0);
    return EXIT_SUCCESS;
}
