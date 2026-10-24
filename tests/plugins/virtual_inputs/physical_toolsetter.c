#include "vinput_host.h"
int main(void)
{
    vi_start(true);
    vi_physical(Probe_Toolsetter, true);
    CHECK(hal.probe.get_state().triggered == !VI_SEPARATE);
    vi_configure(true, true);
    CHECK(hal.probe.get_state().triggered == VI_SEPARATE);
    vi_physical(Probe_Toolsetter, false);
    CHECK(hal.probe.get_state().triggered);
    vi_configure(false, false);
#if VI_SEPARATE
    vi_select(Probe_Toolsetter);
    vi_physical(Probe_Toolsetter, true);
    vi_configure(true, true);
    CHECK(!hal.probe.get_state().triggered);
    vi_physical(Probe_Toolsetter, false);
    CHECK(hal.probe.get_state().triggered);
    vi_configure(false, false);
#endif
    return 0;
}
