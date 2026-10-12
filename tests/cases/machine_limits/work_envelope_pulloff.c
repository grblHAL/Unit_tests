#include "support/control_host.h"
#include "check.h"

int main(void)
{
    coord_data_t pull = {.values = {2, 0, 0}}; limits_homing_pulloff(&pull);
    settings.axis[0].max_travel = -100; sys.homed.mask = sys.homing.mask = 1; settings.limits.flags.hard_enabled = 1;
    limits_set_work_envelope(); NEAR(sys.work_envelope.min.values[0], -98); NEAR(sys.work_envelope.max.values[0], -2);
    return EXIT_SUCCESS;
}
