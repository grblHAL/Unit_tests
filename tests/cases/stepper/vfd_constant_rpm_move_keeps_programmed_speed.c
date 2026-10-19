#include "support/vfd_css_motion_host.h"
int main(void)
{
    prepare_vfd_css_motion();
    vfd_block("G97M3S500");
    CHECK(vfd_state.on && vfd_command_rpm == 500);
    queue_motion_program("G1X20F300");
    vfd_expected_fixed_rpm = 500;
    vfd_check_fixed_rpm = true;
    execute_motion_program();
    for(unsigned i = 0; i < vfd_rpm_calls; i++) CHECK(vfd_rpm_log[i] == 500);
    CHECK(physical_position[X_AXIS] == 1600 && axis_pulses[X_AXIS] == 1600);
    return EXIT_SUCCESS;
}
