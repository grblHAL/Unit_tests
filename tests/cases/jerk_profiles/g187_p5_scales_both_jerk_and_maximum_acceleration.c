#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program(); settings.axis[X_AXIS].acceleration=100; settings.axis[X_AXIS].jerk=100;
    char profile[]="G187P5"; CHECK(gc_execute_block(profile)==Status_OK);
    queue_motion_program("G1X10F100"); plan_block_t *block=plan_get_current_block();
    CHECK(block->condition.jerk); NEAR(block->jerk,20); NEAR(block->max_acceleration,20);
    CHECK(block->acceleration > 16); CHECK(block->acceleration < 17);
    return EXIT_SUCCESS;
}
