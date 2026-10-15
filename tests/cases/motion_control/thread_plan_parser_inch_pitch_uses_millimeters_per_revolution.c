#include "support/thread_plan_host.h"
int main(void)
{
    prepare_thread_parser_plan();
    CHECK(css_block("G20") == Status_OK);
    CHECK(css_block("G76Z0.5P0.05I0.1J0.05K0.1") == Status_OK);
    CHECK(thread_move_count > 1 && thread_moves[1].data.spindle.state.synchronized);
    if(fabsf(thread_moves[1].data.feed_rate - 1.27f) >= .00001f)
        fprintf(stderr, "G20 G76 P0.05: expected 1.27 mm/rev, observed %g mm/rev\n", thread_moves[1].data.feed_rate);
    NEAR(thread_moves[1].data.feed_rate, 1.27f);
    return EXIT_SUCCESS;
}
