#include "support/engine_host.h"
#include "probe.h"
#include "check.h"
static bool read_input(void *input) { return *(bool *)input; }
int main(void)
{
    engine_prepare();
    bool input = false;
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_RisingFalling, &input, read_input));
    CHECK(hal.probe.get_caps(Probe_Default).available);
    CHECK(hal.probe.get_caps(Probe_Default).latchable);
    CHECK(!hal.probe.get_caps(Probe_2).available);
    return EXIT_SUCCESS;
}
