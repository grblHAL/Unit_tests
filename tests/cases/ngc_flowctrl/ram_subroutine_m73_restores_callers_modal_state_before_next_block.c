#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_root_protocol("G21G90G17F120\nO10SUB\nM73\nG20G91G18F10\nO10ENDSUB\nO10CALL\n#100=#<_metric>\n#101=#<_absolute>\n");
    NEAR(ram_flow_parameter(100), 1);
    NEAR(ram_flow_parameter(101), 1);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    NEAR(gc_state.feed_rate, 120);
    CHECK(ngc_modal_state_get() == NULL);
    return EXIT_SUCCESS;
}
