#include "support/program_end_host.h"

int main(void)
{
    prepare_program_end(true);
    parser_state_t *state = gc_get_state();
    CHECK(state == &gc_state);
    CHECK(program_block("G20G91G18") == Status_OK);
    CHECK(state->modal.units_imperial);
    CHECK(state->modal.distance_incremental);
    CHECK(state->modal.plane_select == PlaneSelect_ZX);
    CHECK(program_block("G21G90G17") == Status_OK);
    CHECK(!state->modal.units_imperial);
    CHECK(!state->modal.distance_incremental);
    CHECK(state->modal.plane_select == PlaneSelect_XY);
    return EXIT_SUCCESS;
}
