#include "support/g95_motion_clock_host.h"
int main(void)
{
    prepare_clocked_g95(100, 200, 6000);
    plan_feed_override(50, 100);
    queue_motion_program("G95G1Z10F1");
    execute_motion_program();
    check_clocked_g95_end();
    float before = measured_g95_feed(0, 1), after = measured_g95_feed(2, 3);
    fprintf(stderr, "G95 feed with 50 percent override: %g / %g mm/min\n",
            (double)before, (double)after);
    CHECK(fabsf(before - 50) < .2f);
    CHECK(fabsf(after - 100) < .2f);
    CHECK(sys.override.feed_rate == 50);
    return EXIT_SUCCESS;
}
