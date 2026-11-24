#include "support/jog_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_jog_motion();
    settings.axis[X_AXIS].acceleration = 36000;
    CHECK(system_command("$J=G91X1F100") == Status_OK);
    plan_block_t *block = plan_get_current_block();
    CHECK(block != NULL && block->condition.jog_motion);
    NEAR(block->acceleration, 36000);
    finish_jog_motion();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    NEAR(gc_state.modal.acceleration_factor, 1);
    return EXIT_SUCCESS;
}
