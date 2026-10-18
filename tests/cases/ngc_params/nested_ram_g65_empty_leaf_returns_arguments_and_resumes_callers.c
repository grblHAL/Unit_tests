#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_macro_protocol("#1=3\nG65P10A5\nG91\n", "#1=9\nG65P20A7\nG21\n", "");
    for(unsigned i = 0; i < 3; i++) CHECK(ram_macro_errors[i] == 0 && ram_return_status[i] == Status_OK);
    NEAR(ram_return_arguments[0], 3); NEAR(ram_return_arguments[1], 9); NEAR(ram_return_arguments[2], 7);
    CHECK(gc_state.modal.distance_incremental && !gc_state.modal.units_imperial);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    return EXIT_SUCCESS;
}
