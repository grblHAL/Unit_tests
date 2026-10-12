#include "support/named_parameter_host.h"
#include "check.h"

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
    return EXIT_SUCCESS;
}
