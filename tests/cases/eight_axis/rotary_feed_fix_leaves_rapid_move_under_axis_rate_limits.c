#include "support/motion_program_host.h"
#include "support/settings_host.h"
int main(void)
{
    prepare_motion_program();
    CHECK(store_setting(Settings_RotaryAxes, "1") == Status_OK);
    CHECK(store_setting(Setting_RotaryOptions, "3") == Status_OK);
    queue_motion_program("G0X1A1");
    plan_block_t *block = plan_get_current_block();
    CHECK(block->condition.rapid_motion && !block->condition.inverse_time);
    NEAR(block->programmed_rate, block->rapid_rate);
    execute_motion_program();
    CHECK(physical_position[X_AXIS] == 80 && physical_position[A_AXIS] == 80);
    return EXIT_SUCCESS;
}
