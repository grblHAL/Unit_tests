#include "support/thread_plan_host.h"
#include "check.h"

int main(void)
{
    prepare_thread_plan();
    gc_thread_data thread = basic_thread();
    thread.infeed_angle = 45;
    capture_thread(&thread);
    CHECK(thread_move_count == 8);
    NEAR(thread_moves[0].xyz[Z_AXIS], 0.5f);
    NEAR(thread_moves[2].xyz[Z_AXIS], 10.5f);
    NEAR(thread_moves[4].xyz[Z_AXIS], 0.0f);
    return EXIT_SUCCESS;
}
