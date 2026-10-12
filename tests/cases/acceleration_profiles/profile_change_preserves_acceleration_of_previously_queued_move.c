#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program(); settings.axis[X_AXIS].acceleration = 36000;
    queue_motion_program("G187P2G1X10F100"); plan_block_t *first = plan_get_current_block();
    queue_motion_program("G187P5G1X20F100"); plan_block_t *second = plan_get_recent_block();
    CHECK(first && second && first != second);
    NEAR(first->acceleration, 28800); NEAR(second->acceleration, 7200);
    NEAR(first->target_mm[X_AXIS], 10); NEAR(second->target_mm[X_AXIS], 20);
    return EXIT_SUCCESS;
}
