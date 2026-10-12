#include "support/control_host.h"
#include "check.h"

int main(void)
{
    limits_init(); sys.homed.mask = 1; settings.axis[0].max_travel = -100;
    work_envelope_t envelope = {.min.values = {-100, -100, -100}, .max.values = {0, 0, 0}};
    float target[N_AXIS] = {10, 999, 999}; grbl.apply_travel_limits(target, NULL, &envelope);
    NEAR(target[0], 0); NEAR(target[1], 999); target[0] = -110; grbl.apply_travel_limits(target, NULL, &envelope); NEAR(target[0], -100);
    return EXIT_SUCCESS;
}
