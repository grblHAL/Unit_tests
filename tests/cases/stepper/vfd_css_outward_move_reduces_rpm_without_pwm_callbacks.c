#include "support/vfd_css_motion_host.h"
int main(void)
{
    prepare_vfd_css_motion();
    vfd_block("G96M3S60D1000");
    queue_motion_program("G1X80F300");
    execute_motion_program();
    check_vfd_css_ramp(false, 119.3662f);
    CHECK(physical_position[X_AXIS] == 6400 && axis_pulses[X_AXIS] == 3200);
    return EXIT_SUCCESS;
}
