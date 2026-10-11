#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    sys.homed.mask = 7;
    float midz = (sys.work_envelope.min.z + sys.work_envelope.max.z) * 0.5f;
    float position[N_AXIS] = {0, 0, midz};
    float target[N_AXIS] = {-1 * 1000.0f, 0, midz};
    grbl.apply_travel_limits(target, position, &sys.work_envelope);
    CHECK(isfinite(target[X_AXIS]));
    CHECK(target[X_AXIS] * -1 > 0.0f && target[X_AXIS] * -1 < 1000.0f);
    NEAR(target[Y_AXIS], 0.0f);
    NEAR(target[Z_AXIS], midz);
    coord_data_t cartesian = {.x = target[0], .y = target[1], .z = target[2]}, motors;
    kinematics.transform_from_cartesian(&motors, &cartesian);
    CHECK(isfinite(motors.x) && isfinite(motors.y) && isfinite(motors.z));
    return EXIT_SUCCESS;
}
