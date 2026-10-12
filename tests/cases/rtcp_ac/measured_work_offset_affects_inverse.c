#include "support/rtcp_host.h"
#include "check.h"

int main(void)
{
    prepare_rtcp();
    zero_rtcp_centers();
    gc_state.modal.g5x_offset.data.coord.x = 5;
    gc_state.modal.g5x_offset.data.coord.y = 6;
    gc_state.modal.g5x_offset.data.coord.z = 7;
    rtcp_command(852);
    rtcp_command(851);
    mpos_t steps = {0};
    coord_data_t result;
    kinematics.transform_steps_to_cartesian(&result, &steps);
    NEAR(result.x, -5);
    NEAR(result.y, -6);
    NEAR(result.z, -7);
    return EXIT_SUCCESS;
}
