#include "support/queued_motion_rejection_host.h"
#include "ngc_params.h"
int main(void)
{
    prepare_motion_program();
    CHECK(ngc_param_set(100, 99));
    queue_motion_program("G1X1F100");
    check_rejected_block_preserves_queued_motion("#100=#[2-0.001]", Status_GcodeCommandValueNotInteger);
    float value;
    CHECK(ngc_param_get(100, &value));
    NEAR(value, 99);
    return EXIT_SUCCESS;
}
