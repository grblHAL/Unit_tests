#include "support/control_host.h"
#include "check.h"

int main(void)
{
    settings.axis[0].max_travel = -100; sys.homed.mask = 1;
    limits_set_work_envelope(); NEAR(sys.work_envelope.min.values[0], -100); NEAR(sys.work_envelope.max.values[0], 0);
    NEAR(sys.work_envelope.min.values[1], 0); NEAR(sys.work_envelope.max.values[1], 0);
    return EXIT_SUCCESS;
}
