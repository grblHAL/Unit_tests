#include "relay_host.h"
int main(void)
{
    prepare_relays();
    probe_select_ptr original = hal.probe.select;
    initialize_relays();
    CHECK(relay_details);
    relay_details->restore();
    set_relay_port(Setting_RelayPortToolsetter, -1);
    set_relay_port(Setting_RelayPortProbe2, -1);
    relay_details->save();
    relay_details->load();
    CHECK(saves == 2 && warnings == 1);
    CHECK(hal.probe.select == original && !hal.driver_cap.toolsetter && !hal.driver_cap.probe2);
    CHECK(writes == 0 && delays == 0);
    return 0;
}
