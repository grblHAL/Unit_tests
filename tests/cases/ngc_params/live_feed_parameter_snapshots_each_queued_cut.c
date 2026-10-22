#include "support/virtual_feed_motion_host.h"
int main(void)
{
    prepare_motion_program();
    register_cut_feed();
    queue_motion_program("G91G1X1F#<_hal[plasmac.cut-feed-rate]>");
    plan_block_t *first = plan_get_current_block();
    NEAR(first->programmed_rate, 100);
    live_cut_feed = 200;
    queue_motion_program("G91G1X1F#<_hal[plasmac.cut-feed-rate]>");
    CHECK(plan_get_current_block() == first);
    NEAR(first->programmed_rate, 100);
    NEAR(first->next->programmed_rate, 200);
    live_cut_feed = 300;
    NEAR(first->next->programmed_rate, 200);
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 160 && physical_position[X_AXIS] == 160);
    CHECK(sys.position[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
