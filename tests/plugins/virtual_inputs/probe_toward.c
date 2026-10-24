#include "vinput_host.h"
int main(void)
{
    vi_start(true);
    vi_configure(false, true);
    CHECK(!hal.probe.get_state().triggered);
    CHECK(virtual_input_set(VInput_Probe, true));
    CHECK(hal.probe.get_state().triggered);
    CHECK(hal.probe.is_triggered(Probe_Default));
    CHECK(virtual_input_set(VInput_Probe, false));
    CHECK(!hal.probe.get_state().triggered);
    vi_physical(Probe_Default, true);
    CHECK(hal.probe.get_state().triggered);
    vi_configure(false, false);
    return 0;
}
