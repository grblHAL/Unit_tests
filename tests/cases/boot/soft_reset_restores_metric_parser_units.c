#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    boot_program = "G20\n\x18$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(!gc_state.modal.units_imperial);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    const char *first = strstr(engine_output, "GrblHAL 1.1f");
    CHECK(first && strstr(first + 1, "GrblHAL 1.1f"));
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    return EXIT_SUCCESS;
}
