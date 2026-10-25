#include "relay_host.h"
int main(void)
{
    prepare_relays();
    hal.probe.select = NULL;
    initialize_relays();
    CHECK(relay_details);
    relay_details->load();
    CHECK(hal.probe.select && hal.probe.select(Probe_Toolsetter));
    CHECK(levels[1] && !levels[0]);
    CHECK(hal.probe.select(Probe_2) && !levels[1] && levels[0]);
    CHECK(hal.probe.select(Probe_Default) && !levels[1] && !levels[0]);
    CHECK(selections == 0 && delays == 3 && writes == 6);
    return 0;
}
