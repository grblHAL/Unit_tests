#include "support/thread_plan_host.h"
int main(void)
{
    prepare_thread_parser_plan();
    CHECK(css_block("G20") == Status_OK);
    CHECK(css_block("G76Z0.5P0.05I0.1J0.05K0.1") == Status_OK);
    CHECK(thread_move_count > 1);
    NEAR(thread_moves[0].xyz[X_AXIS], 3.81f);
    float final_cut_x = 0;
    unsigned cuts = 0;
    for(unsigned i = 0; i < thread_move_count; i++)
        if(thread_moves[i].data.spindle.state.synchronized && !thread_moves[i].data.condition.rapid_motion) {
            final_cut_x = thread_moves[i].xyz[X_AXIS];
            NEAR(thread_moves[i].xyz[Z_AXIS], 12.7f);
            cuts++;
        }
    CHECK(cuts >= 2);
    NEAR(final_cut_x, 5.08f);
    NEAR(thread_moves[1].xyz[Z_AXIS], 12.7f);
    NEAR(thread_moves[thread_move_count - 1].xyz[X_AXIS], 0);
    NEAR(gc_state.position[Z_AXIS], 12.7f);
    return EXIT_SUCCESS;
}
