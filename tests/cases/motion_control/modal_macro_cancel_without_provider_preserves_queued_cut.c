#include "support/queued_motion_rejection_host.h"
int main(void)
{
    prepare_motion_program();
    grbl.on_macro_execute = NULL;
    queue_motion_program("G1X1F100");
    check_rejected_block_preserves_queued_motion("G67", Status_GcodeUnsupportedCommand);
    CHECK(ngc_call_level() == 0 && gc_state.g66_args == NULL);
    return EXIT_SUCCESS;
}
