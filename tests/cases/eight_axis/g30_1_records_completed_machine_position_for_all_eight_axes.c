#include "support/canned_motion_host.h"

int main(void)
{
    prepare_canned_motion();
    CHECK(N_AXIS == 8);
    execute_canned("G1X1Y2Z3A4B5C6U7V8F100");
    CHECK(canned_block("G30.1") == Status_OK);
    coord_system_data_t saved;
    CHECK(settings_read_coord_data(CoordinateSystem_G30, &saved));
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == (int32_t)(80 * (axis + 1)));
        CHECK(physical_position[axis] == sys.position[axis]);
        NEAR(saved.coord.values[axis], (float)(axis + 1));
    }
    return EXIT_SUCCESS;
}
