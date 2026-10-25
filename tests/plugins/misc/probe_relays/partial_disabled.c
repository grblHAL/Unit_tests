#include "relay_host.h"
int main(void)
{
    prepare_relays();
    initialize_relays();
    CHECK(relay_details);
    relay_details->restore();
    set_relay_port(Setting_RelayPortToolsetter, -1);
    relay_details->save();
    relay_details->load();
    CHECK(!hal.driver_cap.toolsetter && hal.driver_cap.probe2);
    CHECK(hal.probe.select(Probe_2) && levels[0]);
    CHECK(!hal.probe.select(Probe_Toolsetter));
    CHECK(levels[0] && delays == 1 && writes == 1);
    CHECK(hal.probe.select(Probe_Default) && !levels[0]);
    CHECK(delays == 2 && writes == 2);
    return 0;
}
