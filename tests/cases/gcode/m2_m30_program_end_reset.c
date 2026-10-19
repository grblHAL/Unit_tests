#include "support/program_end_host.h"
int main(void)
{
    prepare_program_end(false);
    CHECK(program_block("G91G18G20G93") == Status_OK);
    CHECK(program_block("M2") == Status_OK);
    CHECK(gc_state.modal.motion == MotionMode_Linear);
    CHECK(!gc_state.modal.distance_incremental && gc_state.modal.plane_select == PlaneSelect_XY);
    CHECK(gc_state.modal.feed_mode == FeedMode_UnitsPerMin && gc_state.modal.units_imperial);
    CHECK(program_complete_calls == 1 && program_completion == ProgramFlow_CompletedM2);
    CHECK(program_block("G91G19G21") == Status_OK);
    CHECK(program_block("M30") == Status_OK);
    CHECK(program_complete_calls == 2 && program_completion == ProgramFlow_CompletedM30);
    CHECK(!gc_state.modal.distance_incremental && gc_state.modal.plane_select == PlaneSelect_XY);
    CHECK(!gc_state.modal.coolant.value && !actual_coolant.value);
    return EXIT_SUCCESS;
}
