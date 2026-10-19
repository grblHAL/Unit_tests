#include "support/incoming_gcode_host.h"
int main(void)
{
    prepare_incoming_parser();
    CHECK(incoming_block("G18") == Status_OK);
    CHECK(incoming_block("M70") == Status_OK);
    CHECK(incoming_block("G70Q100") == Status_GcodeUnsupportedCommand);
    CHECK(incoming_block("G71Q100") == Status_GcodeUnsupportedCommand);
    CHECK(incoming_block("G72Q100") == Status_GcodeUnsupportedCommand);
    CHECK(incoming_block("M72") == Status_OK);
    CHECK(gc_state.modal.plane_select == PlaneSelect_ZX);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
