#include "support/engine_host.h"
#include "probe.h"
#include "check.h"
static bool read_input(void *input) { return *(bool *)input; }
int main(void)
{
    engine_prepare();
    bool inputs[3] = {false};
    CHECK(probe_add(Probe_Default, 0, IRQ_Mode_None, &inputs[0], read_input));
    CHECK(probe_add(Probe_2, 1, IRQ_Mode_None, &inputs[1], read_input));
    CHECK(probe_add(Probe_Toolsetter, 2, IRQ_Mode_None, &inputs[2], read_input));
    CHECK(!probe_add(Probe_Default, 3, IRQ_Mode_None, &inputs[0], read_input));
    return EXIT_SUCCESS;
}
