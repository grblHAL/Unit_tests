#include "support/sender_spindle_override_host.h"
int main(void)
{
    spindle_ptrs_t *spindle = prepare_sender_spindle_override();
    send_spindle_override(CMD_OVERRIDE_SPINDLE_FINE_PLUS);
    CHECK(spindle->param->override_pct == 101);
    RPM_NEAR(driver_rpm, 5050);
    CHECK(rpm_update_calls == 1 && override_event_calls == 1);
    return EXIT_SUCCESS;
}
