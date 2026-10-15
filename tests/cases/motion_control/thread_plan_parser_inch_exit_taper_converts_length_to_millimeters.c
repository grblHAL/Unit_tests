#include "support/thread_plan_host.h"
int main(void)
{
    prepare_thread_parser_plan();
    CHECK(css_block("G20") == Status_OK);
    CHECK(css_block("G76Z0.5P0.05I0.1J0.05K0.1E0.125L2") == Status_OK);
    CHECK(thread_move_count > 2);
    if(fabsf(thread_moves[1].xyz[Z_AXIS] - 9.525f) >= .00001f)
        fprintf(stderr, "G20 G76 E0.125: expected taper start Z9.525 mm, observed Z%g mm\n", thread_moves[1].xyz[Z_AXIS]);
    NEAR(thread_moves[1].xyz[Z_AXIS], 9.525f);
    NEAR(thread_moves[2].xyz[Z_AXIS], 12.7f);
    return EXIT_SUCCESS;
}
