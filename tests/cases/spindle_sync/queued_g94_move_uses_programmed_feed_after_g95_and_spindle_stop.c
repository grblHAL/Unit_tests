#include "support/g95_motion_clock_host.h"
int main(void)
{
    prepare_clocked_g95(100, 0, 3300);
    queue_motion_program("G95G1Z5F1");
    queue_motion_program("G94G1Z10F150");
    execute_motion_program();
    check_clocked_g95_end();
    float before = measured_g95_feed(0, 1), after = measured_g95_feed(2, 3);
    fprintf(stderr, "Measured feed across G95/G94: %g / %g mm/min\n",
            (double)before, (double)after);
    CHECK(fabsf(before - 100) < .2f);
    CHECK(fabsf(after - 150) < .5f);
    CHECK(sync_motion_feedback.rpm == 0 && gc_state.modal.feed_mode == FeedMode_UnitsPerMin);
    return EXIT_SUCCESS;
}
