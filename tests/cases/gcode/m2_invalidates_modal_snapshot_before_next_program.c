#include "support/program_end_host.h"
int main(void)
{
    prepare_program_end(false);
    CHECK(program_block("G90G17F100") == Status_OK);
    CHECK(program_block("M70") == Status_OK);
    CHECK(program_block("M2") == Status_OK);
    CHECK(program_block("G91G19F23") == Status_OK);
    CHECK(program_block("M72") == Status_OK);
    CHECK(gc_state.modal.distance_incremental && gc_state.modal.plane_select == PlaneSelect_YZ);
    NEAR(gc_state.feed_rate, 23);
    return EXIT_SUCCESS;
}
