#include "support/delta_api_host.h"

int main(void)
{
    prepare_delta_api();
    sys.homed.mask = X_AXIS_BIT | Y_AXIS_BIT | Z_AXIS_BIT;
    float midz = (sys.work_envelope.min.z + sys.work_envelope.max.z) * 0.5f;
    float position[N_AXIS] = {0, 0, midz};
    const float requested[N_AXIS] = {0, 1000, 0};
    float target[N_AXIS];
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        target[axis] = position[axis] + requested[axis];
    grbl.apply_travel_limits(target, position, &sys.work_envelope);
    float fraction = 0.0f;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(isfinite(target[axis]));
        if(requested[axis] != 0.0f) {
            float along_axis = (target[axis] - position[axis]) / requested[axis];
            CHECK(along_axis > 0.0f && along_axis < 1.0f);
            if(fraction != 0.0f) CHECK(fabsf(fraction - along_axis) < 0.0001f);
            fraction = along_axis;
        } else NEAR(target[axis], position[axis]);
    }
    coord_data_t cartesian, motors;
    memcpy(cartesian.values, target, sizeof(target));
    kinematics.transform_from_cartesian(&motors, &cartesian);
    CHECK(isfinite(motors.x) && isfinite(motors.y) && isfinite(motors.z));
    CHECK(grbl.check_travel_limits(target, sys.homed, true, &sys.work_envelope));
    return EXIT_SUCCESS;
}
