#include "support/boot_delta_homing_host.h"
int main(void)
{
    prepare_boot_delta_homing(true);
    CHECK(grbl_enter() == 0);
    CHECK(boot_delta_home_finished && boot_delta_home_events == 1);
    CHECK(sys.homed.mask == AXES_BITMASK);
    NEAR(sys.home_position[Z_AXIS], sys.work_envelope.max.z);
    coord_data_t final;
    mpos_t steps;
    memcpy(&steps, sys.position, sizeof(steps));
    kinematics.transform_steps_to_cartesian(&final, &steps);
    CHECK(fabsf(final.x) < .15f && fabsf(final.y) < .15f);
    CHECK(fabsf(final.z - sys.home_position[Z_AXIS]) < .15f);
    for(unsigned axis = 0; axis < 3; axis++)
        CHECK(boot_motor_pulses[axis] > boot_delta_homing_pulses[axis]);
    CHECK(plan_get_current_block() == NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
