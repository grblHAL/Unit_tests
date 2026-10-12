#include "support/wall_host.h"
#include "check.h"

int main(void)
{
    prepare_wall();
    mpos_t steps = {.values = {10000, 10000, 240}};
    coord_data_t result;
    CHECK(kinematics.transform_steps_to_cartesian(&result, &steps) == &result);
    NEAR(result.x, 100);
    NEAR(result.y, 75);
    NEAR(result.z, 3);
    return EXIT_SUCCESS;
}
