#include "support/named_parameter_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    sys.homing.mask = X_AXIS_BIT | Z_AXIS_BIT;
    sys.homed.mask = X_AXIS_BIT;
    NEAR(read_named_parameter("_homed_state"), 0);
    sys.homed.mask |= Z_AXIS_BIT;
    NEAR(read_named_parameter("_homed_state"), 1);
    NEAR(read_named_parameter("_homed_axes"), X_AXIS_BIT | Z_AXIS_BIT);
    return EXIT_SUCCESS;
}
