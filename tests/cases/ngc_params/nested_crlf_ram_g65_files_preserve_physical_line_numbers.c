#include "support/ram_macro_protocol_host.h"
int main(void)
{
    run_ram_macro_protocol("#1=3\r\nG65P10A5\r\nG91\r\n", "#1=9\r\nG65P20A7\r\nG21\r\n", "#1=17\r\nG18\r\n");
    for(unsigned i = 0; i < 3; i++) CHECK(ram_macro_errors[i] == 0 && ram_return_status[i] == Status_OK);
    fprintf(stderr, "Physical line counts: main=%lu sub=%lu leaf=%lu\n", (unsigned long)ram_return_lines[0], (unsigned long)ram_return_lines[1], (unsigned long)ram_return_lines[2]);
    CHECK(ram_return_lines[0] == 3 && ram_return_lines[1] == 3 && ram_return_lines[2] == 2);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);
    CHECK(!gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    return EXIT_SUCCESS;
}
