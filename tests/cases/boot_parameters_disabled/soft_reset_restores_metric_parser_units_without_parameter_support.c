#include "support/boot_host.h"
#if NGC_PARAMETERS_ENABLE || NGC_EXPRESSIONS_ENABLE
#error This case requires the parameters-disabled configuration
#endif
int main(void)
{
    boot_program = "G20\n\x18$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    CHECK(!gc_state.modal.units_imperial);
    const char *welcome = strstr(engine_output, "GrblHAL 1.1f");
    CHECK(welcome && strstr(welcome + 1, "GrblHAL 1.1f"));
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G90") != NULL);
    return EXIT_SUCCESS;
}
