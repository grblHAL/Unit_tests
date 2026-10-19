#include "support/boot_host.h"
int main(void)
{
    boot_program = "G20G91F2\n\x83";
    CHECK(grbl_enter() == 0);
    CHECK(gc_state.modal.units_imperial && gc_state.modal.distance_incremental);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G20 G91 G94") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
