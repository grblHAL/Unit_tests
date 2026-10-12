#include "support/thread_plan_host.h"
#include "check.h"

int main(void)
{
    prepare_thread_plan();
    gc_thread_data thread = basic_thread();
    capture_thread(&thread);
    CHECK(thread_move_count == 7);
    CHECK(!thread_moves[0].data.overrides.feed_hold_disable);
    CHECK(thread_moves[1].data.overrides.feed_hold_disable);
    CHECK(thread_moves[1].data.spindle.state.synchronized);
    CHECK(!thread_moves[3].data.overrides.feed_hold_disable);
    CHECK(!thread_moves[3].data.spindle.state.synchronized);
    CHECK(thread_moves[3].data.condition.rapid_motion);
    return EXIT_SUCCESS;
}
