#include "support/cutter_capture_host.h"
int main(void)
{
    prepare_cutter_capture();
    tool_data_t before = *grbl.tool_table.get_tool(2)->data;
    CHECK(cutter_block("G41.1D6") == Status_OK);
    CHECK(cutter_block("G10L1P2X99") == Status_CutterCompConflict);
    CHECK(memcmp(&before, grbl.tool_table.get_tool(2)->data, sizeof(before)) == 0);
    CHECK(gc_state.modal.cutter_comp.side == CComp_Left);
    CHECK(cutter_enable_calls == 1 && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
