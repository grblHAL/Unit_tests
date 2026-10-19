#include "support/incoming_macro_host.h"
int main(void)
{
    prepare_incoming_macro();
    CHECK(incoming_block("G90G17M70") == Status_OK);
    CHECK(incoming_block("G66P100X12") == Status_OK);
    CHECK(incoming_block("G67") == Status_OK);
    CHECK(incoming_block("G91G18") == Status_OK);
    CHECK(incoming_block("M72") == Status_OK);
    CHECK(!gc_state.modal.distance_incremental && gc_state.modal.plane_select == PlaneSelect_XY);
    CHECK(gc_state.g66_args == NULL && ngc_call_level() == 0);
    CHECK(macro_calls == 0);
    return EXIT_SUCCESS;
}
