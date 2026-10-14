#include "support/sender_spindle_override_host.h"
int main(void)
{
    spindle_ptrs_t *spindle = prepare_sender_spindle_override();
    spindle_set_override(spindle, 150);
    unsigned calls = rpm_update_calls;
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_COARSE_PLUS));
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_RESET));
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_FINE_MINUS));
    CHECK(protocol_exec_rt_system());
    CHECK(spindle->param->override_pct == 99);
    RPM_NEAR(driver_rpm, 4950);
    NEAR(gc_spindle_get(0)->rpm, 5000);
    CHECK(rpm_update_calls == calls + 1);
    return EXIT_SUCCESS;
}
