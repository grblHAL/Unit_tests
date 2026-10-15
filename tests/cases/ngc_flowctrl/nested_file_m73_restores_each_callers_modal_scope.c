#include "support/flow_program_host.h"

int main(void)
{
    CHECK(run_flow_program(
        "G21G90G17F120\n"
        "O10SUB\nM73\nG20G91G18F10\nO20CALL\n#100=#<_imperial>\n#101=#<_incremental>\nO10ENDSUB\n"
        "O20SUB\nM73\nG21G90G19F400\nO20ENDSUB\n"
        "O10CALL\n") == Status_OK);
    NEAR(flow_program_parameter(100), 1);
    NEAR(flow_program_parameter(101), 1);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    NEAR(gc_state.feed_rate, 120);
    CHECK(ngc_call_level() == 0 && ngc_modal_state_get() == NULL);
    return EXIT_SUCCESS;
}
