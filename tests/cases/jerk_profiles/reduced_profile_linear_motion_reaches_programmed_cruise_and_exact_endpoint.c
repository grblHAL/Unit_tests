#include "support/fast_jerk_motion_host.h"
int main(void)
{
    prepare_fast_jerk_motion();
    fast_expected_feed = 5000;
    queue_motion_program("G187P5G1X300F5000");
    CHECK(plan_get_current_block()->condition.jerk);
    finish_fast_motion(0, 0, false);
    return EXIT_SUCCESS;
}
