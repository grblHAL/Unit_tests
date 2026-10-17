#include "support/boot_probe_protection_host.h"
int main(void)
{
    boot_during_init = install_probe_protection;
    boot_control_signals.probe_triggered = true;
    boot_program = "G91\n$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(!settings.probe.enable_protection);
    CHECK(strstr(engine_output, "ALARM:") == NULL && strstr(engine_output, "error:") == NULL);
    CHECK(gc_state.modal.distance_incremental);
    return EXIT_SUCCESS;
}
