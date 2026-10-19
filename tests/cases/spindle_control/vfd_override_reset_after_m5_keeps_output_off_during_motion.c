#include "support/vfd_css_motion_host.h"
int main(void)
{
    prepare_vfd_css_motion();
    vfd_block("G97M3S500");
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_COARSE_MINUS));
    CHECK(protocol_exec_rt_system());
    vfd_block("M5");
    CHECK(!vfd_state.on && vfd_live_rpm == 0);
    unsigned updates = vfd_rpm_calls;
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_RESET));
    CHECK(protocol_exec_rt_system());
    CHECK(!vfd_state.on && vfd_live_rpm == 0);
    queue_motion_program("G1X20F300");
    execute_motion_program();
    CHECK(!vfd_state.on && vfd_live_rpm == 0);
    /* Re-sending zero RPM while disabled is valid; count no required calls. */
    for(unsigned i = updates; i < vfd_rpm_calls; i++) CHECK(vfd_rpm_log[i] == 0);
    CHECK(physical_position[X_AXIS] == 1600 && axis_pulses[X_AXIS] == 1600);
    return EXIT_SUCCESS;
}
