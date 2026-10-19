#include "support/fast_jerk_motion_host.h"
int main(void)
{
    prepare_fast_jerk_motion();
    fast_expected_feed = 5000;
    queue_motion_program("G187P5G1X300Y150Z75F5000");
    queue_motion_program("G187P1G1X0Y0Z0");
    finish_fast_motion(150, 75, true);
    return EXIT_SUCCESS;
}
