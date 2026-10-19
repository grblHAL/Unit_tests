#include "support/vfd_css_motion_host.h"
int main(void)
{
    prepare_vfd_css_motion();
    vfd_block("G7G96M3S60D1000");
    queue_motion_program("G1X40F300");
    execute_motion_program();
    check_vfd_css_ramp(true, 477.4648f);
    CHECK(physical_position[X_AXIS] == 1600 && axis_pulses[X_AXIS] == 1600);
    return EXIT_SUCCESS;
}
