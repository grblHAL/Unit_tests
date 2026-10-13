#include "support/square_host.h"
#include "machine_limits.h"

int main(void)
{
    prepare_square();
    settings.axis[3].steps_per_mm = 80.5f;
    coord_data_t pulloff = {.values = {1, 2, 3, 2}};
    limits_homing_pulloff(&pulloff);
    sys.position[X_AXIS] = 160; sys.position[Z_AXIS] = 320;
    kinematics.limits_set_machine_positions((axes_signals_t){.mask = Y_AXIS_BIT | (1u << 3)});
    CHECK(sys.position[Y_AXIS] == -160 && sys.position[3] == -161);
    CHECK(sys.position[X_AXIS] == 160 && sys.position[Z_AXIS] == 320);
    NEAR(sys.home_position[Y_AXIS], -2);
    return EXIT_SUCCESS;
}
