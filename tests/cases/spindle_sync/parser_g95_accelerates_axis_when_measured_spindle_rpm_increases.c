#include "support/g95_motion_clock_host.h"
int main(void)
{
    prepare_clocked_g95(100, 200, 3000);
    queue_motion_program("G95G1Z10F1");
    execute_motion_program();
    check_clocked_g95_end();
    float before = measured_g95_feed(0, 1), after = measured_g95_feed(2, 3);
    fprintf(stderr, "Measured G95 feed before/after RPM increase: %g / %g mm/min\n",
            (double)before, (double)after);
    CHECK(fabsf(before - 100) < .2f);
    CHECK(fabsf(after - 200) < .5f);
    return EXIT_SUCCESS;
}
