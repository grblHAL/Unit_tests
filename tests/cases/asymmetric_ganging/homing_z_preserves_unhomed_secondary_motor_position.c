#include "support/ganging_host.h"
#include "machine_limits.h"

int main(void)
{
    prepare_ganging();
    coord_data_t pulloff = {.values = {1, 1, 2, 1}};
    limits_homing_pulloff(&pulloff);
    sys.home_position[Y_AXIS] = -1;
    sys.position[Y_AXIS] = -400; sys.position[3] = -400;
    kinematics.limits_set_machine_positions((axes_signals_t){.mask = Z_AXIS_BIT});
    CHECK(sys.position[Z_AXIS] == -160);
    CHECK(sys.position[Y_AXIS] == -400);
    fprintf(stderr, "secondary Y position after Z homing: %ld, expected -400\n", (long)sys.position[3]);
    CHECK(sys.position[3] == -400);
    return EXIT_SUCCESS;
}
