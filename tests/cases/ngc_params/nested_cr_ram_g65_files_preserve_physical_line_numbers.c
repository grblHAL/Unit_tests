#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_macro_protocol("#1=3\rG65P10A5\rG91\r", "#1=9\rG65P20A7\rG21\r", "#1=17\rG18\r");
    for(unsigned i = 0; i < 3; i++) CHECK(ram_macro_errors[i] == 0 && ram_return_status[i] == Status_OK);
    CHECK(ram_return_lines[0] == 3 && ram_return_lines[1] == 3 && ram_return_lines[2] == 2);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);
    CHECK(!gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    return EXIT_SUCCESS;
}
