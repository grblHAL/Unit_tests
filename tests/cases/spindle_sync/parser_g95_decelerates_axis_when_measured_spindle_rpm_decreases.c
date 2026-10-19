#include "support/g95_motion_clock_host.h"
int main(void)
{
    prepare_clocked_g95(200, 100, 1500);
    queue_motion_program("G95G1Z10F1");
    execute_motion_program();
    check_clocked_g95_end();
    float before = measured_g95_feed(0, 1), after = measured_g95_feed(2, 3);
    fprintf(stderr, "Measured G95 feed before/after RPM decrease: %g / %g mm/min\n",
            (double)before, (double)after);
    CHECK(fabsf(before - 200) < .5f);
    CHECK(fabsf(after - 100) < .2f);
    return EXIT_SUCCESS;
}
