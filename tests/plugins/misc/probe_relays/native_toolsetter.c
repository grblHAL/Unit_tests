#include "relay_host.h"
int main(void)
{
    native_toolsetter = true;
    load_relays();
    const setting_detail_t *tool = relay_setting(Setting_RelayPortToolsetter);
    const setting_detail_t *second = relay_setting(Setting_RelayPortProbe2);
    CHECK(!tool->is_available(tool, 0) && second->is_available(second, 0));
    CHECK(get_relay_port(tool->id) == -1 && get_relay_port(second->id) == 1);
    CHECK(hal.probe.select(Probe_2) && levels[1]);
    CHECK(hal.probe.select(Probe_Toolsetter) && !levels[1]);
    CHECK(selections == 2 && delays == 2 && writes == 2 && warnings == 0);
    return 0;
}
