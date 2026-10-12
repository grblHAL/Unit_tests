#include "support/thread_plan_host.h"
#include "check.h"

int main(void)
{
    prepare_thread_plan();
    gc_thread_data thread = basic_thread();
    thread.z_final = -10;
    capture_thread(&thread);
    CHECK(thread_move_count == 7);
    NEAR(thread_moves[1].xyz[Z_AXIS], -10.0f);
    NEAR(thread_moves[3].xyz[Z_AXIS], 0.0f);
    NEAR(thread_moves[5].xyz[Z_AXIS], -10.0f);
    return EXIT_SUCCESS;
}
