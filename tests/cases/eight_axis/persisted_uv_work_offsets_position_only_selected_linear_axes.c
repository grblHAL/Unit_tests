#include "support/canned_motion_host.h"

int main(void)
{
    prepare_canned_motion();
    CHECK(N_AXIS == 8);
    CHECK(canned_block("G10L2P2U2V3") == Status_OK);
    execute_canned("G55G1U1V2F100");
    CHECK(physical_position[6] == 240 && sys.position[6] == 240);
    CHECK(physical_position[7] == 400 && sys.position[7] == 400);
    CHECK(axis_pulses[6] == 240 && axis_pulses[7] == 400);
    for(unsigned axis = 0; axis < 6; axis++) CHECK(axis_pulses[axis] == 0);
    coord_system_data_t saved;
    CHECK(settings_read_coord_data(CoordinateSystem_G55, &saved));
    NEAR(saved.coord.values[6], 2);
    NEAR(saved.coord.values[7], 3);
    return EXIT_SUCCESS;
}
