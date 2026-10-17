#include "support/boot_probe_protection_host.h"
int main(void)
{
    boot_protection_enabled = false;
    boot_during_init = install_probe_protection;
    boot_control_signals.probe_triggered = true;
    boot_program = "G91\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "ALARM:") == NULL && strstr(engine_output, "error:") == NULL);
    CHECK(gc_state.modal.distance_incremental);
    CHECK(strstr(engine_output, "[GC:G0 G54 G17 G21 G91") != NULL);
    return EXIT_SUCCESS;
}
