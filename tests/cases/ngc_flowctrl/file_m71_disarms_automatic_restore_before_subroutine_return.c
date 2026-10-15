#include "support/flow_program_host.h"

int main(void)
{
    CHECK(run_flow_program(
        "G21G90G17F120\n"
        "O10SUB\nM73\nG20G91G18F10\nM71\nO10ENDSUB\n"
        "O10CALL\n#100=#<_imperial>\n") == Status_OK);
    NEAR(flow_program_parameter(100), 1);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);
    NEAR(gc_state.feed_rate, 254);
    CHECK(ngc_call_level() == 0 && ngc_modal_state_get() == NULL);
    return EXIT_SUCCESS;
}
