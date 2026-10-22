#include "support/queued_motion_rejection_host.h"

int main(void)
{
    prepare_motion_program();
    coord_system_data_t before, after;
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &before));
    queue_motion_program("G1X1F100");
    check_rejected_block_preserves_queued_motion("G20G91G10L2P-1X5", Status_NegativeValue);
    CHECK(settings_read_coord_data(CoordinateSystem_G54, &after));
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        NEAR(after.coord.values[axis], before.coord.values[axis]);
    return EXIT_SUCCESS;
}
