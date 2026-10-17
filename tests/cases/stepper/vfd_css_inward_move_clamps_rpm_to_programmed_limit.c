#include "support/vfd_css_motion_host.h"
int main(void)
{
    prepare_vfd_css_motion();
    vfd_block("G96M3S60D1000");
    queue_motion_program("G1X1F300");
    execute_motion_program();
    check_vfd_css_ramp(true, 1000);
    CHECK(physical_position[X_AXIS] == 80 && axis_pulses[X_AXIS] == 3120);
    return EXIT_SUCCESS;
}
