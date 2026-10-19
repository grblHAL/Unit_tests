#include "support/fast_jerk_motion_host.h"
#include "support/fast_short_hold_host.h"
int main(void)
{
    prepare_fast_jerk_motion();
    execute_fast_short_segment_hold();
    return EXIT_SUCCESS;
}
