#include "support/vfd_css_motion_host.h"
int main(void)
{
    prepare_vfd_css_motion();
    vfd_block("G96M3S60D1000");
    queue_motion_program("G1Z10F300");
    vfd_expected_fixed_rpm = 238.7324f;
    vfd_check_fixed_rpm = true;
    execute_motion_program();
    for(unsigned i = 0; i < vfd_rpm_calls; i++) CHECK(fabsf(vfd_rpm_log[i] - 238.7324f) < 1);
    CHECK(physical_position[X_AXIS] == 3200 && axis_pulses[X_AXIS] == 0);
    CHECK(physical_position[Z_AXIS] == 800 && axis_pulses[Z_AXIS] == 800);
    return EXIT_SUCCESS;
}
