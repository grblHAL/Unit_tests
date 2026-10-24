#include "relay_host.h"
int main(void)
{
    claims_ok = false;
    prepare_relays();
    probe_select_ptr original = hal.probe.select;
    initialize_relays();
    CHECK(relay_details);
    relay_details->load();
    CHECK(hal.probe.select == original && !hal.driver_cap.toolsetter && !hal.driver_cap.probe2);
    CHECK(warnings == 1 && writes == 0 && delays == 0);
    return 0;
}
