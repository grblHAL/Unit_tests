#include "support/cutter_capture_host.h"

int main(void)
{
    prepare_cutter_capture();
    CHECK(cutter_block("F120M70") == Status_OK);
    CHECK(cutter_block("F240") == Status_OK);
    CHECK(cutter_enable_calls == 0);
    CHECK(cutter_block("M72") == Status_OK);
    NEAR(gc_state.feed_rate, 120);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Off);
    NEAR(gc_state.modal.cutter_comp.radius, 0);
    CHECK(cutter_enable_calls == 0);
    CHECK(plan_get_current_block() == NULL);
    CHECK(cutter_block("M71") == Status_OK);
    return EXIT_SUCCESS;
}
