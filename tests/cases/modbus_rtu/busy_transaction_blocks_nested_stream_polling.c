#include "support/rtu_host.h"
#include "check.h"
static unsigned blocking_callbacks;
static void blocking_foreground(sys_state_t state) { (void)state; blocking_callbacks++; }

int main(void)
{
    prepare_rtu();
    grbl.on_execute_realtime = blocking_foreground;
    send_request();
    CHECK(modbus_isbusy());
    CHECK(stream_tx_blocking());
    CHECK(blocking_callbacks == 0);
    return EXIT_SUCCESS;
}
