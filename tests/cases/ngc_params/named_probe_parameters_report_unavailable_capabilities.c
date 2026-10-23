#include "support/named_parameter_host.h"
#include "check.h"

static bool legacy_contact;
static probe_state_t legacy_probe_state(void)
{
    return (probe_state_t){.connected = true, .triggered = legacy_contact,
        .probe_id = Probe_Default};
}
int main(void)
{
    engine_parser_prepare();
    hal.driver_cap.probe = false;
    hal.driver_cap.probe2 = false;
    hal.driver_cap.toolsetter = false;
    hal.probe.get_state = NULL;
    NEAR(read_named_parameter("_probe_state"), -1);
    NEAR(read_named_parameter("_probe2_state"), -1);
    NEAR(read_named_parameter("_toolsetter_state"), -1);
    NEAR(read_named_parameter("_active_probe"), -1);
    // Legacy drivers may expose state without the optional per-probe helper.
    CHECK(hal.probe.is_triggered == NULL);
    hal.driver_cap.probe = true;
    hal.probe.get_state = legacy_probe_state;
    NEAR(read_named_parameter("_active_probe"), Probe_Default);
    NEAR(read_named_parameter("_probe_state"), -1);
    CHECK(!hal.probe.get_state().triggered);
    legacy_contact = true;
    CHECK(hal.probe.get_state().triggered);
    NEAR(read_named_parameter("_probe_state"), -1);
    NEAR(read_named_parameter("_probe2_state"), -1);
    NEAR(read_named_parameter("_toolsetter_state"), -1);
    return EXIT_SUCCESS;
}
