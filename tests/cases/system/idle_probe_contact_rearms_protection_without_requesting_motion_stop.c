#include "support/system_probe_guard_irq_host.h"
int main(void)
{
    prepare_system_probe_guard();
    unsigned installs = guard_irq_installs;
    guard_probe_input = true;
    guard_irq_callback(0, true);
    CHECK(guard_irq_installs == installs + 1);
    CHECK(sys.last_event.control.probe_triggered);
    check_idle_guard_state(true);
    return EXIT_SUCCESS;
}
