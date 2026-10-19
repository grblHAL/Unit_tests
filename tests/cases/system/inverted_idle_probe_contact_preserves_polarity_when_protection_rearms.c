#include "support/system_probe_guard_irq_host.h"
int main(void)
{
    guard_probe_input = true;
    prepare_system_probe_guard();
    CHECK(system_command("$6=1") == Status_OK);
    check_idle_guard_state(false);
    unsigned installs = guard_irq_installs;
    guard_probe_input = false;
    guard_irq_callback(0, false);
    CHECK(guard_irq_installs == installs + 1);
    check_idle_guard_state(true);
    return EXIT_SUCCESS;
}
