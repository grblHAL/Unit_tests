#include "support/queued_motion_rejection_host.h"
#include "ngc_params.h"
int main(void)
{
    prepare_motion_program();
    queue_motion_program("G1X1F100");
    CHECK(ngc_call_level() == 0);
    check_rejected_block_preserves_queued_motion("O[1/0]CALL", Status_ExpressionDivideByZero);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
