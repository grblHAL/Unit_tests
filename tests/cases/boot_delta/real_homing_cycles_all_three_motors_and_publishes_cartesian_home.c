#include "support/boot_delta_homing_host.h"
int main(void)
{
    prepare_boot_delta_homing(false);
    CHECK(grbl_enter() == 0);
    CHECK(boot_delta_home_finished && boot_delta_home_events == 1);
    CHECK(sys.homed.mask == AXES_BITMASK);
    for(unsigned axis = 0; axis < 3; axis++) CHECK(boot_motor_pulses[axis] > 80);
    NEAR(sys.home_position[X_AXIS], 0);
    NEAR(sys.home_position[Y_AXIS], 0);
    CHECK(fabsf(sys.home_position[Z_AXIS] - (delta_zero_angle_height() - 1)) < .01f);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
