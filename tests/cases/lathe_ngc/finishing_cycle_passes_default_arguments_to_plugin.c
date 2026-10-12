#include "support/lathe_cycle_capture_host.h"
#include "check.h"

int main(void)
{
    prepare_lathe_capture(); CHECK(css_block("G70X10Z20Q7F100") == Status_OK);
    CHECK(lathe_cycle_calls == 1 && lathe_cycle_label == 7);
    CHECK(lathe_cycle_args.motion == MotionMode_LatheFinishing);
    NEAR(lathe_cycle_args.x, 10); NEAR(lathe_cycle_args.z, 20);
    NEAR(lathe_cycle_args.finish.start_distance, 0); NEAR(lathe_cycle_args.finish.end_distance, 0);
    NEAR(lathe_cycle_args.finish.passes, 1); NEAR(lathe_cycle_plan.feed_rate, 100);
    return EXIT_SUCCESS;
}
