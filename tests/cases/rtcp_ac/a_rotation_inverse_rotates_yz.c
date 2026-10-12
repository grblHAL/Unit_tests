#include "support/rtcp_host.h"
#include "check.h"

int main(void)
{
    prepare_rtcp();
    zero_rtcp_centers();
    rtcp_command(851);
    mpos_t steps = {.values = {0, 800, 0, 7200, 0}};
    coord_data_t result;
    kinematics.transform_steps_to_cartesian(&result, &steps);
    NEAR(result.x, 0);
    NEAR(result.y, 0);
    NEAR(result.z, -10);
    NEAR(result.a, 90);
    return EXIT_SUCCESS;
}
