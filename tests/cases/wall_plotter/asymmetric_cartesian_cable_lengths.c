#include "support/wall_host.h"
#include "check.h"

int main(void)
{
    prepare_wall();
    coord_data_t input = {.x = 0, .y = 150}, result;
    kinematics.transform_from_cartesian(&result, &input);
    NEAR(result.x, 150);
    NEAR(result.y, 250);
    return EXIT_SUCCESS;
}
