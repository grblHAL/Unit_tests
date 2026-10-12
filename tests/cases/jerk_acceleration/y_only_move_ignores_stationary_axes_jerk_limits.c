#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program();
    for(unsigned i=0;i<N_AXIS;i++) settings.axis[i].jerk = 1;
    settings.axis[1].jerk = 100;
    queue_motion_program("G1Y10F100"); plan_block_t *block = plan_get_current_block();
    CHECK(block->condition.jerk); NEAR(block->jerk, 100);
    CHECK(block->steps.value[1] == 800);
    return EXIT_SUCCESS;
}
