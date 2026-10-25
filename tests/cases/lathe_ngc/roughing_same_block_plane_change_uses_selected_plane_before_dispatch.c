#include "support/lathe_cycle_capture_host.h"
int main(void)
{
    prepare_lathe_capture();
    CHECK(css_block("G17") == Status_OK);
    CHECK(css_block("G18G71X10Z20Q7F100") == Status_OK);
    CHECK(lathe_cycle_calls == 1 && lathe_cycle_label == 7);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);
    CHECK(lathe_cycle_args.motion == MotionMode_LatheRoughingZ);
    NEAR(lathe_cycle_args.x, 10); NEAR(lathe_cycle_args.z, 20);
    NEAR(lathe_cycle_args.rough.increment, 1);
    NEAR(lathe_cycle_args.rough.retract_distance, .5f);
    return EXIT_SUCCESS;
}
