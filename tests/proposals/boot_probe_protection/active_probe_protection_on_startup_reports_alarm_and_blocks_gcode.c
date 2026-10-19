#include "support/boot_probe_protection_host.h"
int main(void)
{
    boot_during_init = install_probe_protection;
    boot_control_signals.probe_triggered = true;
    boot_program = "G91\n";
    CHECK(grbl_enter() == 0);
    CHECK(strstr(engine_output, "ALARM:13") != NULL);
    CHECK(strstr(engine_output, "Probe protection activated.") != NULL);
    CHECK(strstr(engine_output, "error:9") != NULL);
    CHECK(!gc_state.modal.distance_incremental);
    return EXIT_SUCCESS;
}
