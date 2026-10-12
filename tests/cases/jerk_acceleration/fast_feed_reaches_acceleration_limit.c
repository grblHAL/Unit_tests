#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program(); settings.axis[X_AXIS].acceleration = 100; settings.axis[X_AXIS].jerk = 100;
    queue_motion_program("G1X10F400"); plan_block_t *block = plan_get_current_block();
    CHECK(block->condition.jerk); NEAR(block->jerk, 100); NEAR(block->max_acceleration, 100);
    NEAR(block->acceleration, 80); CHECK(block->steps.value[X_AXIS] == 800);
    return EXIT_SUCCESS;
}
