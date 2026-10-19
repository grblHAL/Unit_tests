#include "support/system_probe_guard_irq_host.h"
int main(void)
{
    prepare_system_probe_guard();
    unsigned installs = guard_irq_installs;
    guard_probe_input = true;
    guard_irq_callback(0, true);
    guard_probe_input = false;
    guard_irq_callback(0, false);
    CHECK(guard_irq_installs == installs + 2);
    check_idle_guard_state(false);
    return EXIT_SUCCESS;
}
