#include "support/virtual_feed_motion_host.h"
int main(void)
{
    prepare_motion_program();
    register_cut_feed();
    queue_motion_program("G1X1F100");
    plan_block_t *first = plan_get_current_block();
    live_cut_feed = -50;
    CHECK(cut_feed_block("G1X2F#<_hal[plasmac.cut-feed-rate]>") == Status_NegativeValue);
    CHECK(plan_get_current_block() == first);
    NEAR(first->programmed_rate, 100);
    NEAR(gc_state.feed_rate, 100);
    NEAR(gc_state.position[X_AXIS], 1);
    live_cut_feed = 200;
    queue_motion_program("G1X2F#<_hal[plasmac.cut-feed-rate]>");
    NEAR(first->next->programmed_rate, 200);
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 160 && physical_position[X_AXIS] == 160);
    CHECK(sys.position[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
