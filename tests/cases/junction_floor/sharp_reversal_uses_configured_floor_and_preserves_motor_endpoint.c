#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    CHECK(MINIMUM_JUNCTION_SPEED == 5.0f);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        char acceleration[] = "1";
        CHECK(settings_store_setting(Setting_AxisAcceleration + axis, acceleration) == Status_OK);
    }
    queue_motion_program("G1X1F100");
    NEAR(plan_get_current_block()->entry_speed_sqr, 0);
    queue_motion_program("G1X0Y0.0125");
    plan_block_t *corner = plan_get_recent_block();
    NEAR(corner->max_junction_speed_sqr, 25);
    NEAR(corner->entry_speed_sqr, 25);
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == 0 && physical_position[Y_AXIS] == 1);
    CHECK(axis_pulses[X_AXIS] == 160 && axis_pulses[Y_AXIS] == 1 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
