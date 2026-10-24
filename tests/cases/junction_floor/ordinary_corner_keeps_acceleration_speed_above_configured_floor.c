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
    queue_motion_program("G1Y1");
    plan_block_t *corner = plan_get_recent_block();
    CHECK(corner->max_junction_speed_sqr > 25);
    CHECK(corner->entry_speed_sqr > 25);
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == 80 && physical_position[Y_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 80 && axis_pulses[Y_AXIS] == 80 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
