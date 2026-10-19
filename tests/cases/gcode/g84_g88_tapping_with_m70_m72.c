#include "support/canned_spindle_host.h"
int main(void)
{
    prepare_canned_spindle();
    CHECK(canned_block("G17M3S1000") == Status_OK);
    CHECK(canned_block("M70") == Status_OK);
    execute_canned("G84X1Z-2R1P0F100");
    CHECK(gc_state.modal.motion == MotionMode_CannedCycle84);
    CHECK(canned_block("G80") == Status_OK);
    CHECK(canned_block("G88X1Z-2R1F100") == Status_GcodeUnsupportedCommand);
    CHECK(canned_block("M72") == Status_OK);
    CHECK(!gc_state.modal.canned_cycle_active);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
