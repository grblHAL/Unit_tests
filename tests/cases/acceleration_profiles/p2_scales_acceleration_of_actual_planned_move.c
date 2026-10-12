#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program(); settings.axis[X_AXIS].acceleration = 36000;
    char profile[] = "G187P2"; CHECK(gc_execute_block(profile) == Status_OK);
    queue_motion_program("G1X10F100");
    plan_block_t *block = plan_get_current_block(); CHECK(block != NULL);
    NEAR(gc_state.modal.acceleration_factor, 0.8f);
    NEAR(block->acceleration, 28800); CHECK(block->steps.value[X_AXIS] == 800);
    return EXIT_SUCCESS;
}
