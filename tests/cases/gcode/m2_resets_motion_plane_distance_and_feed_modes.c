#include "support/program_end_host.h"
#include "check.h"

int main(void)
{
    prepare_program_end(true);
    CHECK(program_block("G18G91G93F2") == Status_OK);
    CHECK(program_block("M2") == Status_OK);
    CHECK(gc_state.modal.motion == MotionMode_Linear);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    CHECK(!gc_state.modal.distance_incremental);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMin);
    CHECK(gc_state.modal.program_flow == ProgramFlow_Running);
    return EXIT_SUCCESS;
}
