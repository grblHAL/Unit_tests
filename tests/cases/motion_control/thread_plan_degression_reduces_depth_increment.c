#include "support/thread_plan_host.h"
#include "check.h"

int main(void)
{
    prepare_thread_plan();
    gc_thread_data thread = basic_thread();
    thread.depth_degression = 2;
    capture_thread(&thread);
    CHECK(thread_move_count == 15);
    NEAR(thread_moves[0].xyz[X_AXIS], 1.5f);
    NEAR(thread_moves[4].xyz[X_AXIS], 1.0f + 0.5f * sqrtf(2.0f));
    NEAR(thread_moves[8].xyz[X_AXIS], 1.0f + 0.5f * sqrtf(3.0f));
    NEAR(thread_moves[12].xyz[X_AXIS], 2.0f);
    return EXIT_SUCCESS;
}
