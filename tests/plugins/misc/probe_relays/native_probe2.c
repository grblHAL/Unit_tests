#include "relay_host.h"
int main(void)
{
    native_probe2 = true;
    load_relays();
    CHECK(get_relay_port(Setting_RelayPortToolsetter) == 1);
    CHECK(get_relay_port(Setting_RelayPortProbe2) == -1);
    CHECK(hal.probe.select(Probe_Toolsetter) && levels[1]);
    CHECK(hal.probe.select(Probe_2) && !levels[1]);
    CHECK(selections == 2 && delays == 2 && writes == 2 && warnings == 0);
    return 0;
}
