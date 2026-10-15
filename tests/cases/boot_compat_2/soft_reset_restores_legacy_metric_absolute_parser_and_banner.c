#include "support/boot_legacy_host.h"
#include "check.h"

int main(void)
{
    boot_program = "G20G91\n\x18$G\n";
    run_legacy_boot_program();
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    CHECK(strstr(engine_output, "Grbl " GRBL_VERSION) != NULL);
    CHECK(strstr(engine_output, "GrblHAL ") == NULL);
    CHECK(boot_setup_calls == 1);
    return EXIT_SUCCESS;
}
