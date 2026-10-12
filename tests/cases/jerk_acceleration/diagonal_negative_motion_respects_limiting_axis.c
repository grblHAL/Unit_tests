#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program();
    settings.axis[X_AXIS].jerk=100; settings.axis[Y_AXIS].jerk=40;
    queue_motion_program("G1X-3Y-4F100"); plan_block_t *block = plan_get_current_block();
    CHECK(block->condition.jerk); NEAR(block->jerk,50);
    CHECK(block->jerk * 0.6f <= settings.axis[X_AXIS].jerk);
    NEAR(block->jerk * 0.8f, settings.axis[Y_AXIS].jerk);
    CHECK(block->steps.value[X_AXIS] == 240); CHECK(block->steps.value[Y_AXIS] == 320);
    return EXIT_SUCCESS;
}
