#include "relay_host.h"
int main(void)
{
    load_relays();
    set_relay_port(Setting_RelayPortToolsetter, 0);
    set_relay_port(Setting_RelayPortProbe2, 1);
    relay_details->save();
    CHECK(get_relay_port(Setting_RelayPortToolsetter) == 0 &&
          get_relay_port(Setting_RelayPortProbe2) == 1);
    // Port settings require reboot; an active selection keeps the claimed mapping.
    CHECK(hal.probe.select(Probe_Toolsetter) && levels[1] && !levels[0]);
    CHECK(hal.probe.select(Probe_2) && !levels[1] && levels[0]);
    CHECK(saves == 2 && delays == 2 && writes == 4);
    return 0;
}
