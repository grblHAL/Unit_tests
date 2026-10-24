#include "support/motion_program_host.h"
#include "support/settings_host.h"
int main(void)
{
    prepare_motion_program();
    CHECK(store_setting(Settings_RotaryAxes, "1") == Status_OK);
    CHECK(store_setting(Setting_RotaryOptions, "3") == Status_OK);
    queue_motion_program("G21G1A2F120");
    plan_block_t *block = plan_get_current_block();
    CHECK(!block->condition.inverse_time);
    NEAR(block->programmed_rate, 120);
    execute_motion_program();
    CHECK(physical_position[A_AXIS] == 160 && axis_pulses[A_AXIS] == 160);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        if(axis != A_AXIS) CHECK(axis_pulses[axis] == 0 && physical_position[axis] == 0);
    return EXIT_SUCCESS;
}
