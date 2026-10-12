#include "support/rtcp_host.h"
#include "check.h"

int main(void)
{
    prepare_rtcp();
    mpos_t steps = {.values = {80, -160, 240, 7200, 14400}};
    coord_data_t result;
    CHECK(kinematics.transform_steps_to_cartesian(&result, &steps) == &result);
    NEAR(result.x, 1);
    NEAR(result.y, -2);
    NEAR(result.z, 3);
    NEAR(result.a, 90);
    NEAR(result.c, 180);
    return EXIT_SUCCESS;
}
