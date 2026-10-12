#include "support/control_host.h"
#include "check.h"

int main(void)
{
    settings.homing.cycle[0].mask = 1; settings.homing.cycle[1].mask = 2;
    sys.homed.mask = 7; limits_set_homing_axes(); CHECK(sys.homing.mask == 3); CHECK(sys.homed.mask == 3);
    return EXIT_SUCCESS;
}
