#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    settings.homing.dir_mask.mask = 5;
    float rate = kinematics.homing_cycle_get_feedrate((axes_signals_t){.mask = 7}, 150, HomingMode_Seek);
    NEAR(rate, 150.0f);
    coord_data_t target = {0}, position = {0};
    CHECK(kinematics.transform_from_cartesian(&target, &position) == &target);
    NEAR(target.x, -(float)M_PI);
    NEAR(target.y, (float)M_PI);
    NEAR(target.z, -(float)M_PI);
    return EXIT_SUCCESS;
}
