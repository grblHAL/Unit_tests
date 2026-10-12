#include "support/named_parameter_host.h"
#include "check.h"
static probe_state_t selected_probe(void) { return (probe_state_t){ .probe_id = Probe_Toolsetter }; }
int main(void)
{
    engine_parser_prepare();
    hal.probe.get_state = selected_probe;
    NEAR(read_named_parameter("_active_probe"), Probe_Toolsetter);
    return EXIT_SUCCESS;
}
