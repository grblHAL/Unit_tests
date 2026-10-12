#include "support/named_parameter_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    sys.homing.mask = 0;
    settings.homing.flags.single_axis_commands = false;
    settings.homing.flags.manual = false;
    sys.homed.mask = AXES_BITMASK;
    NEAR(read_named_parameter("_homed_state"), 0);
    NEAR(read_named_parameter("_homed_axes"), AXES_BITMASK);
    return EXIT_SUCCESS;
}
