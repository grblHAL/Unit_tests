#include "vinput_host.h"
int main(void)
{
    vi_start(true);
    CHECK(virtual_input_set(VInput_Probe, true) && virtual_input_set(VInput_Toolsetter, true));
    vi_select(Probe_2);
    CHECK(!hal.probe.get_state().triggered && !hal.probe.is_triggered(Probe_2));
    vi_physical(Probe_2, true);
    CHECK(hal.probe.get_state().triggered && hal.probe.is_triggered(Probe_2));
    return 0;
}
