#include "support/thread_plan_host.h"
#include "check.h"

int main(void)
{
    prepare_thread_plan();
    gc_thread_data thread = basic_thread();
    thread.end_taper_type = Taper_Exit;
    thread.end_taper_length = 2;
    capture_thread(&thread);
    CHECK(thread_move_count == 9);
    NEAR(thread_moves[1].xyz[Z_AXIS], 8.0f);
    NEAR(thread_moves[2].xyz[X_AXIS], 0.5f);
    NEAR(thread_moves[2].xyz[Z_AXIS], 10.0f);
    return EXIT_SUCCESS;
}
