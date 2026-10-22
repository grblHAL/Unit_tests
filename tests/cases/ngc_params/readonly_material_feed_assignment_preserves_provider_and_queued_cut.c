#include "support/virtual_feed_motion_host.h"
int main(void)
{
    prepare_motion_program();
    register_cut_feed();
    queue_motion_program("G1X1F#<_hal[plasmac.cut-feed-rate]>");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    CHECK(cut_feed_block("#<_hal[plasmac.cut-feed-rate]>=200") == Status_BadNumberFormat);
    NEAR(live_cut_feed, 100);
    CHECK(plan_get_current_block() == first && plan_get_block_buffer_available() == available);
    NEAR(first->programmed_rate, 100);
    NEAR(gc_state.position[X_AXIS], 1);
    queue_motion_program("G1X2F#<_hal[plasmac.cut-feed-rate]>");
    NEAR(first->next->programmed_rate, 100);
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 160 && physical_position[X_AXIS] == 160);
    CHECK(sys.position[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
