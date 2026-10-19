#include "support/thread_plan_host.h"
int main(void)
{
    prepare_thread_parser_plan();
    CHECK(css_block("G7") == Status_OK);
    CHECK(css_block("G76Z10P1I2J1K2") == Status_OK);
    CHECK(thread_move_count == 7);
    NEAR(thread_moves[0].xyz[X_AXIS], 1.5f);
    NEAR(thread_moves[4].xyz[X_AXIS], 2);
    NEAR(thread_moves[1].xyz[Z_AXIS], 10);
    NEAR(thread_moves[1].data.feed_rate, 1);
    CHECK(gc_state.modal.diameter_mode);
    return EXIT_SUCCESS;
}
