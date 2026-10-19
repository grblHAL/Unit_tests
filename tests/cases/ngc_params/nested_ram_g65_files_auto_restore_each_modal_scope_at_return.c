#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_macro_protocol("#1=3\nG21G90\nG65P10A5\n", "M73\nG20G91\nG65P20A7\n", "M73\nG18\n");
    for(unsigned i = 0; i < 3; i++) CHECK(ram_macro_errors[i] == 0 && ram_return_status[i] == Status_OK);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    float parent; CHECK(ngc_param_get(1, &parent)); NEAR(parent, 3);
    return EXIT_SUCCESS;
}
