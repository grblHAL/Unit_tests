#include "support/virtual_feed_motion_host.h"
static unsigned selections;
static status_code_t select_finish(char *text)
{
    CHECK(strcmp(text, "Select finish") == 0);
    selections++;
    live_cut_feed = 200;
    return Status_OK;
}
int main(void)
{
    prepare_motion_program();
    register_cut_feed();
    queue_motion_program("G1X1F#<_hal[plasmac.cut-feed-rate]>");
    plan_block_t *first = plan_get_current_block();
    CHECK(live_feed_reads == 1);
    grbl.on_gcode_comment = select_finish;
    queue_motion_program("G1X2F#<_hal[plasmac.cut-feed-rate]>(Select finish)");
    CHECK(selections == 1 && live_feed_reads == 2);
    NEAR(first->programmed_rate, 100);
    NEAR(first->next->programmed_rate, 200);
    live_cut_feed = 300;
    queue_motion_program("G1X3");
    CHECK(selections == 1 && live_feed_reads == 2);
    NEAR(first->next->next->programmed_rate, 200);
    NEAR(gc_state.feed_rate, 200);
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 240 && physical_position[X_AXIS] == 240);
    CHECK(sys.position[X_AXIS] == 240);
    return EXIT_SUCCESS;
}
