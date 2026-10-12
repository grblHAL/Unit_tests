#include "support/engine_host.h"
#include "probe.h"
#include "check.h"
static bool read_input(void *input) { return *(bool *)input; }
int main(void)
{
    engine_prepare();
    bool first = false, second = true;
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_None, &first, read_input));
    CHECK(probe_add(Probe_2, 1, IRQ_Mode_None, &second, read_input));
    hal.probe.configure(false, true);
    CHECK(!hal.probe.select(Probe_2));
    CHECK(hal.probe.get_state().probe_id == Probe_Default);
    return EXIT_SUCCESS;
}
