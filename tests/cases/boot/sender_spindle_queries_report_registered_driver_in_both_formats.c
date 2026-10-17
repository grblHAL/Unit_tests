#include "support/boot_spindle_setup_host.h"
int main(void)
{
    boot_during_init = register_primary_during_init;
    boot_spindle_reference = 10;
    boot_program = "$SPINDLES\n$SPINDLESH\n";
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(spindle_get_count() == 1);
    CHECK(strstr(engine_output, "0 - primary") != NULL);
    CHECK(strstr(engine_output, "[SPINDLE:0|") != NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
