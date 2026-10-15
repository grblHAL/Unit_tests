#include "support/boot_legacy_host.h"
#include "check.h"

static bool saw_imperial_incremental_mode;
static void observe_before_reset(void)
{
    if(boot_reads == sizeof("G20G91\n") - 1)
        saw_imperial_incremental_mode = gc_state.modal.units_imperial &&
                                        gc_state.modal.distance_incremental;
}
int main(void)
{
    boot_program = "G20G91\n\x18$G\n";
    legacy_read_observer = observe_before_reset;
    run_legacy_boot_program();
    CHECK(saw_imperial_incremental_mode);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    CHECK(strstr(engine_output, "Grbl " GRBL_VERSION) != NULL);
    CHECK(strstr(engine_output, "GrblHAL ") == NULL);
    CHECK(boot_setup_calls == 1);
    return EXIT_SUCCESS;
}
