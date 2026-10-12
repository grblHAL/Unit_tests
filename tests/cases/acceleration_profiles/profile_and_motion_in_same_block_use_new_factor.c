#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program(); settings.axis[X_AXIS].acceleration = 36000;
    queue_motion_program("G187P5G1X10F100");
    plan_block_t *block = plan_get_current_block(); CHECK(block != NULL);
    NEAR(block->acceleration, 7200); NEAR(gc_state.modal.acceleration_factor, 0.2f);
    CHECK(block->steps.value[X_AXIS] == 800);
    return EXIT_SUCCESS;
}
