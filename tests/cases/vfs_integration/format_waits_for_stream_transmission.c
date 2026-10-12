#include "support/vfs_format_host.h"
#include "check.h"
static unsigned pending = 3, realtime_calls;
static uint16_t pending_tx(void) { return pending; }
static void advance_transmission(sys_state_t state) { (void)state; CHECK(format_calls == 0); CHECK(pending > 0); pending--; realtime_calls++; }
int main(void)
{
    vfs_drive_t *drive = prepare_format_drive();
    hal.stream.get_tx_buffer_count = pending_tx;
    grbl.on_execute_realtime = advance_transmission;
    CHECK(vfs_drive_format(drive) == 0);
    CHECK(pending == 0 && realtime_calls == 3 && format_calls == 1);
    cleanup_format_drive();
    return EXIT_SUCCESS;
}
