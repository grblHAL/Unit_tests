#include "support/vfd_css_motion_host.h"
int main(void)
{
    prepare_vfd_css_motion();
    vfd_block("G96M3S60D1000");
    CHECK(vfd_state.on);
    queue_motion_program("G1X20F300");
    CHECK(fabsf(plan_get_current_block()->spindle.rpm - 238.7324f) < 1);
    CHECK(vfd_rpm_calls == 0);
    execute_motion_program();
    check_vfd_css_ramp(true, 477.4648f);
    CHECK(physical_position[X_AXIS] == 1600 && axis_pulses[X_AXIS] == 1600);
    return EXIT_SUCCESS;
}
