#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    boot_program = "G20\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(gc_state.modal.units_imperial);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G20 G90") != NULL);
    return EXIT_SUCCESS;
}
