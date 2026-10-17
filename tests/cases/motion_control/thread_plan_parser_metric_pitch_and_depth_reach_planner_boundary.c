#include "support/thread_plan_host.h"
int main(void)
{
    prepare_thread_parser_plan();
    CHECK(css_block("G76Z10P1I1J0.5K1") == Status_OK);
    CHECK(thread_move_count == 7);
    NEAR(thread_moves[0].xyz[X_AXIS], 1.5f);
    NEAR(thread_moves[4].xyz[X_AXIS], 2);
    NEAR(thread_moves[1].xyz[Z_AXIS], 10);
    CHECK(thread_moves[1].data.spindle.state.synchronized);
    CHECK(!thread_moves[1].data.condition.rapid_motion);
    NEAR(thread_moves[1].data.feed_rate, 1);
    NEAR(gc_state.position[Z_AXIS], 10);
    return EXIT_SUCCESS;
}
