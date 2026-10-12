#include "support/named_parameter_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    sys.homing.mask = 0;
    settings.homing.flags.manual = true;
    sys.homed.mask = X_AXIS_BIT;
    NEAR(read_named_parameter("_homed_state"), 0);
    sys.homed.mask = AXES_BITMASK;
    NEAR(read_named_parameter("_homed_state"), 1);
    return EXIT_SUCCESS;
}
