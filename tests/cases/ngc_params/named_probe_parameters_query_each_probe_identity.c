#include "support/named_parameter_host.h"
#include "check.h"
static unsigned seen;
static bool probe_triggered(probe_id_t id) { seen |= 1u << id; return id == Probe_2; }
int main(void)
{
    engine_parser_prepare();
    hal.driver_cap.probe = true;
    hal.driver_cap.probe2 = true;
    hal.driver_cap.toolsetter = true;
    hal.probe.is_triggered = probe_triggered;
    NEAR(read_named_parameter("_probe_state"), 0);
    NEAR(read_named_parameter("_probe2_state"), 1);
    NEAR(read_named_parameter("_toolsetter_state"), 0);
    CHECK(seen == ((1u << Probe_Default) | (1u << Probe_2) | (1u << Probe_Toolsetter)));
    return EXIT_SUCCESS;
}
