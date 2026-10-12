#include "support/rtcp_host.h"
#include "check.h"

int main(void)
{
    prepare_rtcp();
    zero_rtcp_centers();
    rtcp_command(851);
    rtcp_command(850);
    mpos_t steps = {.values = {800, 0, 0, 0, 7200}};
    coord_data_t result;
    kinematics.transform_steps_to_cartesian(&result, &steps);
    NEAR(result.x, 10);
    NEAR(result.y, 0);
    NEAR(result.c, 90);
    return EXIT_SUCCESS;
}
