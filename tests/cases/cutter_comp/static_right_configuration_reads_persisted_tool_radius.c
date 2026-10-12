#include "support/cutter_capture_host.h"
#include "check.h"

int main(void)
{
    prepare_cutter_capture(); tool_data_t tool = {.tool_id = 2, .radius = 2.5f}; CHECK(grbl.tool_table.set_tool(&tool));
    CHECK(cutter_block("G42D2") == Status_OK);
    CHECK(cutter_enable_calls == 1); CHECK(cutter_received.side == CComp_Right && !cutter_received.dynamic);
    NEAR(cutter_received.radius, 2.5f); NEAR(gc_state.modal.cutter_comp.radius, 2.5f);
    return EXIT_SUCCESS;
}
