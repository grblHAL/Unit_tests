#include "support/rtcp_host.h"
#include "check.h"

int main(void)
{
    prepare_rtcp();
    zero_rtcp_centers();
    rtcp_command(851);
    mpos_t steps = {.values = {80, -160, 240, 0, 0}};
    coord_data_t result;
    kinematics.transform_steps_to_cartesian(&result, &steps);
    NEAR(result.x, 1);
    NEAR(result.y, -2);
    NEAR(result.z, 3);
    NEAR(result.a, 0);
    NEAR(result.c, 0);
    return EXIT_SUCCESS;
}
