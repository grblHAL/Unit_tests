#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_macro_protocol("#1=3\nG65P10A5\nG91\n", "#1=9\nG65P20A7\nG20\n", "#1=17\nG999\nG18\n");
    for(unsigned i = 0; i < 3; i++) {
        CHECK(ram_macro_errors[i] >= 1);
        CHECK(ram_return_status[i] == Status_GcodeUnsupportedCommand);
    }
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    CHECK(gc_state.last_error == Status_OK); /* Restored sender query succeeds. */
    float parent; CHECK(ngc_param_get(1, &parent)); NEAR(parent, 3);
    return EXIT_SUCCESS;
}
