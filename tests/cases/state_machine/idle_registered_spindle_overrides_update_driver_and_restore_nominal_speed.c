#include "support/held_running_spindle_override_host.h"
int main(void)
{
    prepare_registered_running_spindle();
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_COARSE_PLUS));
    CHECK(protocol_exec_rt_system());
    CHECK(laser_last_driver_level == 550 && spindle_get(0)->param->override_pct == 110);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_RESET));
    CHECK(protocol_exec_rt_system());
    CHECK(laser_last_driver_level == 500 && spindle_get(0)->param->override_pct == 100);
    CHECK(axis_pulses[X_AXIS] == 0 && state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
