#include "support/sync_parser_host.h"
int main(void)
{
    prepare_sync_parser();
    sync_feedback.rpm = 500;
    CHECK(css_block("M70") == Status_OK);
    CHECK(css_block("G76Z-10P1I-1J0.2K1Q20H1") == Status_OK);
    NEAR(gc_state.position[Z_AXIS], -10);
    CHECK(plan_get_current_block() == NULL);
    CHECK(css_block("M72") == Status_OK);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);

    return EXIT_SUCCESS;
}
