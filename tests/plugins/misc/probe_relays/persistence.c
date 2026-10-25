#include "relay_host.h"
int main(void)
{
    prepare_relays();
    initialize_relays();
    CHECK(relay_details);
    relay_details->restore();
    set_relay_port(Setting_RelayPortToolsetter, 0);
    set_relay_port(Setting_RelayPortProbe2, 1);
    relay_details->save();
    set_relay_port(Setting_RelayPortToolsetter, 1);
    set_relay_port(Setting_RelayPortProbe2, 0);
    relay_details->load();
    CHECK(saves == 2 && warnings == 0);
    CHECK(get_relay_port(Setting_RelayPortToolsetter) == 0 &&
          get_relay_port(Setting_RelayPortProbe2) == 1);
    CHECK(hal.probe.select(Probe_Toolsetter) && levels[0] && !levels[1]);
    CHECK(hal.probe.select(Probe_2) && !levels[0] && levels[1]);
    return 0;
}
