#include "support/canned_motion_host.h"
int main(void)
{
    prepare_canned_motion();
    CHECK(canned_block("G10L2P9X10Y20") == Status_OK);
    CHECK(canned_block("G0X10.3Y20.4Z-5") == Status_OK);
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == 824 && physical_position[Y_AXIS] == 1632);
    CHECK(physical_position[Z_AXIS] == -400);
    CHECK(system_xy_at_fixture(CoordinateSystem_G59_3, .501f));
    CHECK(!system_xy_at_fixture(CoordinateSystem_G59_3, .49f));
    return EXIT_SUCCESS;
}
