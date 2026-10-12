#include "support/engine_host.h"
#include "probe.h"
#include "check.h"
static bool read_input(void *input) { return *(bool *)input; }
int main(void)
{
    engine_prepare();
    bool input = false;
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_None, &input, read_input));
    hal.probe.configure(false, true);
    hal.probe.connected_toggle();
    CHECK(hal.probe.get_state().connected);
    return EXIT_SUCCESS;
}
