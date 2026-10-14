#include "support/sender_spindle_override_host.h"
int main(void)
{
    spindle_ptrs_t *spindle = prepare_sender_spindle_override();
    spindle_set_override(spindle, 150);
    RPM_NEAR(driver_rpm, 7500);
    send_spindle_override(CMD_OVERRIDE_SPINDLE_RESET);
    CHECK(spindle->param->override_pct == 100);
    RPM_NEAR(driver_rpm, 5000);
    CHECK(rpm_update_calls == 2 && override_event_calls == 2);
    return EXIT_SUCCESS;
}
