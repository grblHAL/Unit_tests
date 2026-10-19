#include "support/sync_parser_host.h"
int main(void)
{
    prepare_sync_parser();
    sync_feedback.rpm = 500;
    CHECK(css_block("G76Z-10P1I-1J0.2K1") == Status_OK);
    NEAR(gc_state.position[Z_AXIS], -10);
    CHECK(plan_get_current_block() == NULL);

    return EXIT_SUCCESS;
}
