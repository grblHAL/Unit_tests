#include "support/jog_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_jog_motion();
    settings.axis[X_AXIS].acceleration = 36000;
    char profile[] = "G187P5";
    CHECK(gc_execute_block(profile) == Status_OK);
    CHECK(system_command("$J=G91X-1F100") == Status_OK);
    plan_block_t *block = plan_get_current_block();
    CHECK(block != NULL && block->condition.jog_motion);
    NEAR(block->acceleration, 7200);
    finish_jog_motion();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == -80);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    NEAR(gc_state.modal.acceleration_factor, 0.2f);
    return EXIT_SUCCESS;
}
