#include "support/sync_parser_host.h"
#include "check.h"

int main(void)
{
    prepare_sync_parser();
    sync_feedback.rpm = 0;
    CHECK(css_block("G33Z1K0.1") == Status_GcodeSpindleNotRunning);
    NEAR(gc_state.position[Z_AXIS], 0.0f);
    return EXIT_SUCCESS;
}
