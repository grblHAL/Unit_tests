#include "support/control_host.h"
#include "check.h"

int main(void)
{
    limits_init();
    settings.axis[0].max_travel = -100;
    work_envelope_t envelope = {.min.values = {-100, -100, -100}, .max.values = {0, 0, 0}};
    float target[N_AXIS] = {10, 999, 999};
    float position[N_AXIS] = {-10, -20, -30};
    CHECK(sys.homed.mask == 0);
    grbl.apply_travel_limits(target, NULL, &envelope);
    NEAR(target[0], 10); NEAR(target[1], 999); NEAR(target[2], 999);
    grbl.apply_travel_limits(target, position, &envelope);
    NEAR(target[0], 10); NEAR(target[1], 999); NEAR(target[2], 999);
    NEAR(position[0], -10); NEAR(position[1], -20); NEAR(position[2], -30);
    sys.homed.mask = 1;
    grbl.apply_travel_limits(target, NULL, &envelope);
    NEAR(target[0], 0); NEAR(target[1], 999); target[0] = -110; grbl.apply_travel_limits(target, NULL, &envelope); NEAR(target[0], -100);
    return EXIT_SUCCESS;
}
