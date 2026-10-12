#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    sys.home_position[0] = 1; sys.home_position[1] = 2; sys.home_position[2] = 3;
    kinematics.homing_cycle_get_feedrate((axes_signals_t){.mask = 7}, 100, HomingMode_Seek);
    grbl.on_homing_completed((axes_signals_t){.mask = 7}, false);
    NEAR(sys.home_position[0], 1.0f);
    NEAR(sys.home_position[1], 2.0f);
    NEAR(sys.home_position[2], 3.0f);
    coord_data_t target = {.z = (sys.work_envelope.min.z + sys.work_envelope.max.z) * 0.5f}, motors = {0};
    CHECK(kinematics.transform_from_cartesian(&motors, &target) == &motors);
    CHECK(isfinite(motors.x));
    return EXIT_SUCCESS;
}
