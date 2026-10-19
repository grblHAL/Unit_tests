#include "support/canned_motion_host.h"
int main(void)
{
    prepare_canned_motion();
    CHECK(canned_block("G10L2P9X10Y20") == Status_OK);
    CHECK(canned_block("G10L2P1X5Y7") == Status_OK);
    CHECK(canned_block("G53G0X10Y20Z-5") == Status_OK);
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == 800 && physical_position[Y_AXIS] == 1600);
    CHECK(physical_position[Z_AXIS] == -400);
    CHECK(system_xy_at_fixture(CoordinateSystem_G59_3, .05f));
    NEAR(gc_state.modal.g5x_offset.data.coord.x, 5);
    NEAR(gc_state.modal.g5x_offset.data.coord.y, 7);
    return EXIT_SUCCESS;
}
