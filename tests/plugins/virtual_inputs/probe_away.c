#include "vinput_host.h"
int main(void)
{
    vi_start(true);
    CHECK(virtual_input_set(VInput_Probe, true));
    vi_configure(true, true);
    CHECK(!hal.probe.get_state().triggered);
    CHECK(virtual_input_set(VInput_Probe, false));
    CHECK(hal.probe.get_state().triggered);
    vi_physical(Probe_Default, true);
    CHECK(!hal.probe.get_state().triggered);
    vi_physical(Probe_Default, false);
    CHECK(hal.probe.get_state().triggered);
    vi_configure(false, false);
    return 0;
}
