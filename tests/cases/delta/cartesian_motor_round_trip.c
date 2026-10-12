#include "support/delta_host.h"
#include "check.h"

int main(void)
{
    prepare_delta();
    coord_data_t input = {.x = 10, .y = 5, .z = -300}, motors, result;
    kinematics.transform_from_cartesian(&motors, &input);
    mpos_t steps;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(isfinite(motors.values[axis]));
        settings.axis[axis].steps_per_mm = 1000000;
        steps.values[axis] = lroundf(motors.values[axis] * settings.axis[axis].steps_per_mm);
    }
    kinematics.transform_steps_to_cartesian(&result, &steps);
    CHECK(fabsf(result.x - input.x) < .001f);
    CHECK(fabsf(result.y - input.y) < .001f);
    CHECK(fabsf(result.z - input.z) < .001f);
    return EXIT_SUCCESS;
}
