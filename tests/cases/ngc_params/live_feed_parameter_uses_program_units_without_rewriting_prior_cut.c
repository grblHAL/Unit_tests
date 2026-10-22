#include "support/virtual_feed_motion_host.h"
int main(void)
{
    prepare_motion_program();
    register_cut_feed();
    queue_motion_program("G21G1X1F#<_hal[plasmac.cut-feed-rate]>");
    plan_block_t *first = plan_get_current_block();
    live_cut_feed = 4;
    queue_motion_program("G20G91G1X0.125F#<_hal[plasmac.cut-feed-rate]>");
    NEAR(first->programmed_rate, 100);
    NEAR(first->next->programmed_rate, 101.6f);
    NEAR(gc_state.feed_rate, 101.6f);
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 334 && physical_position[X_AXIS] == 334);
    CHECK(sys.position[X_AXIS] == 334);
    return EXIT_SUCCESS;
}
