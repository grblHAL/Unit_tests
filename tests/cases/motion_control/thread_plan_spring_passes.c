#include "support/thread_plan_host.h"
#include "check.h"

int main(void)
{
    prepare_thread_plan();
    gc_thread_data thread = basic_thread();
    thread.spring_passes = 2;
    capture_thread(&thread);
    CHECK(thread_move_count == 15);
    NEAR(thread_moves[8].xyz[X_AXIS], 2.0f);
    NEAR(thread_moves[12].xyz[X_AXIS], 2.0f);
    NEAR(thread_moves[13].xyz[Z_AXIS], 10.0f);
    return EXIT_SUCCESS;
}
