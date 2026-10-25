#include "vinput_host.h"
int main(void)
{
    vi_start(true);
    CHECK(virtual_input_set(VInput_Toolsetter, true));
    CHECK(hal.probe.is_triggered(Probe_Toolsetter));
    CHECK(hal.probe.get_state().triggered == !VI_SEPARATE);
    vi_configure(true, true);
    CHECK(hal.probe.get_state().triggered == VI_SEPARATE);
    vi_configure(false, false);
#if VI_SEPARATE
    vi_select(Probe_Toolsetter);
    CHECK(hal.probe.get_state().triggered);
    vi_configure(true, true);
    CHECK(!hal.probe.get_state().triggered);
    CHECK(virtual_input_set(VInput_Toolsetter, false));
    CHECK(hal.probe.get_state().triggered);
    vi_configure(false, false);
#endif

    return 0;
}
