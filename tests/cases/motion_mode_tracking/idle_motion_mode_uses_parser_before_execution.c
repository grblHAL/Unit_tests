#include "support/motion_mode_host.h"
int main(void)
{
    prepare_motion_modes();
    CHECK(st_get_motion_mode() == MotionMode_Seek);
    char line[] = "G1F100";
    CHECK(gc_execute_block(line) == Status_OK);
    CHECK(st_get_motion_mode() == MotionMode_Linear);
    CHECK(rapid_steps == 0 && feed_steps == 0);
    return EXIT_SUCCESS;
}
