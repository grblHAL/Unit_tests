#include "support/thread_plan_host.h"
#include "check.h"

int main(void)
{
    prepare_thread_plan();
    gc_thread_data thread = basic_thread();
    capture_thread(&thread);
    CHECK(thread_move_count == 7);
    NEAR(thread_moves[0].xyz[X_AXIS], 1.5f);
    NEAR(thread_moves[1].xyz[Z_AXIS], 10.0f);
    CHECK(thread_moves[0].data.condition.rapid_motion);
    CHECK(thread_moves[1].data.spindle.state.synchronized);
    NEAR(thread_moves[2].xyz[X_AXIS], 0.0f);
    NEAR(thread_moves[3].xyz[Z_AXIS], 0.0f);
    NEAR(thread_moves[4].xyz[X_AXIS], 2.0f);
    NEAR(thread_moves[5].xyz[Z_AXIS], 10.0f);
    NEAR(thread_moves[6].xyz[X_AXIS], 0.0f);
    return EXIT_SUCCESS;
}
