#include "support/control_host.h"
#include "check.h"

int main(void)
{
    settings.axis[0].max_travel = -100; settings.axis[0].steps_per_mm = 80; settings.homing.dir_mask.mask = 1;
    sys.position[1] = 1234; axes_signals_t cycle = {.mask = 1}; limits_set_machine_positions(cycle, false);
    CHECK(sys.position[0] == -8000); NEAR(sys.home_position[0], -100); CHECK(sys.position[1] == 1234);
    settings.homing.flags.force_set_origin = 1; limits_set_machine_positions(cycle, false); CHECK(sys.position[0] == 0);
    return EXIT_SUCCESS;
}
