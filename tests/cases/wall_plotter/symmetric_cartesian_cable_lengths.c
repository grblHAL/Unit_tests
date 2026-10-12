#include "support/wall_host.h"
#include "check.h"

int main(void)
{
    prepare_wall();
    coord_data_t input = {.x = 100, .y = 75, .z = 3}, result;
    CHECK(kinematics.transform_from_cartesian(&result, &input) == &result);
    NEAR(result.x, 125);
    NEAR(result.y, 125);
    NEAR(result.z, 3);
    return EXIT_SUCCESS;
}
