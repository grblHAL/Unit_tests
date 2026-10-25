#include "relay_host.h"
int main(void)
{
    load_relays();
    CHECK(saves == 1 && warnings == 0 && hal.driver_cap.toolsetter && hal.driver_cap.probe2);
    CHECK(get_relay_port(Setting_RelayPortToolsetter) == 1 &&
          get_relay_port(Setting_RelayPortProbe2) == 0);
    CHECK(hal.probe.select(Probe_Toolsetter));
    CHECK(levels[1] && !levels[0] && delays == 1);
    CHECK(hal.probe.select(Probe_2));
    CHECK(!levels[1] && levels[0] && delays == 2);
    CHECK(hal.probe.select(Probe_Default));
    CHECK(!levels[1] && !levels[0] && delays == 3 && selections == 2);
    CHECK(writes == 6);
    return 0;
}
