#include "support/control_host.h"
#include "check.h"

int main(void)
{
    sys.homed.mask = 3; settings.axis[0].max_travel = -100; settings.axis[1].max_travel = -200;
    settings.homing.flags.force_set_origin = 1; settings.homing.dir_mask.mask = 2;
    limits_set_work_envelope(); NEAR(sys.work_envelope.min.values[0], -100); NEAR(sys.work_envelope.max.values[0], 0);
    NEAR(sys.work_envelope.min.values[1], 0); NEAR(sys.work_envelope.max.values[1], 200);
    return EXIT_SUCCESS;
}
