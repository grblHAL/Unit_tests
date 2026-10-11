#include "support/delta_api_host.h"
#include "check.h"

int main(void)
{
    prepare_delta_api();
    kinematics.homing_cycle_get_feedrate((axes_signals_t){.mask = 7}, 25, HomingMode_Pulloff);
    coord_data_t target = {0}, position = {.x = 1};
    CHECK(kinematics.transform_from_cartesian(&target, &position) == &target);
    CHECK(isfinite(target.x) && target.x > 0);
    NEAR(target.y, target.x);
    NEAR(target.z, target.x);
    return EXIT_SUCCESS;
}
