#include "support/control_host.h"
#include "check.h"

int main(void)
{
    limits_init();
    sys.homed.mask = 7;
    for(unsigned axis = 0; axis < 3; axis++) settings.axis[axis].max_travel = -10;
    work_envelope_t envelope = {.min.values = {-10, -10, -10}, .max.values = {0, 0, 0}};
    float position[N_AXIS] = {-5, -5, -5};
    float target[N_AXIS] = {-7,-15,-6};
    grbl.apply_travel_limits(target, position, &envelope);
    NEAR(target[0], -6.0f);
    NEAR(target[1], -10.0f);
    NEAR(target[2], -5.5f);
    return EXIT_SUCCESS;
}
