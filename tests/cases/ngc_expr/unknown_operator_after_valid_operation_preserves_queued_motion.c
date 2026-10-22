#include "support/queued_motion_rejection_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_motion_program();
    CHECK(ngc_param_set(100, 99));
    queue_motion_program("G1X1F100");
    check_rejected_block_preserves_queued_motion("#100=[1+2BOGUS3]", Status_ExpressionUknownOp);
    float value;
    CHECK(ngc_param_get(100, &value));
    NEAR(value, 99);
    char retry[] = "#100=[1+2*3]";
    CHECK(gc_execute_block(retry) == Status_OK);
    CHECK(ngc_param_get(100, &value));
    NEAR(value, 7);
    return EXIT_SUCCESS;
}
