#include "support/motion_program_host.h"
#include "support/settings_host.h"
int main(void)
{
    prepare_motion_program();
    CHECK(store_setting(Settings_RotaryAxes, "17") == Status_OK);
    CHECK(store_setting(Setting_RotaryOptions, "3") == Status_OK);
    queue_motion_program("G1Y3Z4A1V2F120");
    plan_block_t *block = plan_get_current_block();
    CHECK(block->condition.inverse_time);
    NEAR(block->programmed_rate / block->millimeters, 24);
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == 0 && axis_pulses[X_AXIS] == 0);
    CHECK(physical_position[Y_AXIS] == 240 && physical_position[Z_AXIS] == 320);
    CHECK(physical_position[A_AXIS] == 80 && physical_position[7] == 160);
    CHECK(axis_pulses[Y_AXIS] == 240 && axis_pulses[Z_AXIS] == 320);
    CHECK(axis_pulses[A_AXIS] == 80 && axis_pulses[7] == 160);
    CHECK(axis_pulses[4] == 0 && axis_pulses[5] == 0 && axis_pulses[6] == 0);
    return EXIT_SUCCESS;
}
