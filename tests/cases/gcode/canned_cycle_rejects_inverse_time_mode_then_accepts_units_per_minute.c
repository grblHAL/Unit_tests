#include "support/canned_motion_host.h"

int main(void)
{
    prepare_canned_motion();
    CHECK(canned_block("G93") == Status_OK);
    CHECK(canned_block("G81X1Z-1R0F10") == Status_InvalidStatement);
    CHECK(gc_state.modal.feed_mode == FeedMode_InverseTime);
    CHECK(plan_get_current_block() == NULL);
    CHECK(physical_position[X_AXIS] == 0 && physical_position[Z_AXIS] == 0);
    CHECK(canned_block("G94") == Status_OK);
    execute_canned("G81X1Z-1R0F100");
    CHECK(physical_position[X_AXIS] == 80 && physical_position[Z_AXIS] == 0);
    CHECK(axis_pulses[Z_AXIS] == 160);
    return EXIT_SUCCESS;
}
