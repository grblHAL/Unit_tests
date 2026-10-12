#include "support/engine_host.h"
#include "probe.h"
#include "check.h"
static bool read_input(void *input) { return *(bool *)input; }
int main(void)
{
    engine_prepare();
    bool input = false;
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_None, &input, read_input));
    hal.probe.configure(true, true);
    CHECK(hal.probe.get_state().triggered);
    input = true;
    CHECK(!hal.probe.get_state().triggered);
    return EXIT_SUCCESS;
}
