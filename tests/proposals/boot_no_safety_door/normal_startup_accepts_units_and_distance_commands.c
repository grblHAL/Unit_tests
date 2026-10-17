#include "support/boot_host.h"
int main(void)
{
    boot_program = "G20G91\n$G\nG21G90\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G20 G91") != NULL);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    return EXIT_SUCCESS;
}
