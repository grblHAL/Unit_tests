#include "support/fast_jerk_motion_host.h"
int main(void)
{
    prepare_fast_jerk_motion();
    queue_motion_program("G1X300F12000");
    CHECK(plan_get_current_block()->condition.jerk);
    finish_fast_motion(0, 0, false);
    return EXIT_SUCCESS;
}
