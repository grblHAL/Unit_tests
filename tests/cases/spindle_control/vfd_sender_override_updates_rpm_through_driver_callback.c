#include "support/vfd_css_motion_host.h"
int main(void)
{
    prepare_vfd_css_motion();
    vfd_block("G97M3S500");
    for(unsigned i = 0; i < 5; i++) {
        CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_COARSE_MINUS));
        CHECK(protocol_exec_rt_system());
    }
    CHECK(vfd_state.on && vfd_live_rpm == 250);
    CHECK(vfd_rpm_calls > 0 && vfd_rpm_log[vfd_rpm_calls-1] == 250);
    CHECK(protocol_enqueue_realtime_command(CMD_OVERRIDE_SPINDLE_RESET));
    CHECK(protocol_exec_rt_system());
    CHECK(vfd_state.on && vfd_live_rpm == 500);
    return EXIT_SUCCESS;
}
