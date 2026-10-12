#include "support/wall_host.h"
#include "check.h"

int main(void)
{
    prepare_wall();
    mpos_t steps = {.values = {12000, 20000, 0}};
    coord_data_t result;
    kinematics.transform_steps_to_cartesian(&result, &steps);
    NEAR(result.x, 0);
    NEAR(result.y, 150);
    return EXIT_SUCCESS;
}
