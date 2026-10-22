#include "support/cutter_capture_host.h"
#include "state_machine.h"
static void fitted_tool_changed(tool_data_t *tool) { CHECK(tool && tool->tool_id == 2); }
int main(void)
{
    prepare_cutter_capture();
    tool_data_t tool = {.tool_id = 2, .radius = 2.5f};
    CHECK(host_save_tool(&tool));
    grbl.on_tool_changed = fitted_tool_changed;
    state_set(STATE_IDLE);
    CHECK(cutter_block("M61Q2") == Status_OK);
    state_set(STATE_CHECK_MODE);
    CHECK(gc_state.tool->tool_id == 2);
    CHECK(cutter_block("G41") == Status_OK);
    CHECK(cutter_received.side == CComp_Left && !cutter_received.dynamic);
    NEAR(cutter_received.radius, 2.5f);
    CHECK(cutter_block("G40") == Status_OK);
    CHECK(cutter_block("G1X10F100") == Status_OK);
    CHECK(cutter_block("G42D0") == Status_OK);
    CHECK(cutter_received.side == CComp_Right && !cutter_received.dynamic);
    NEAR(cutter_received.radius, 2.5f);
    NEAR(gc_state.modal.cutter_comp.radius, 2.5f);
    CHECK(gc_state.tool->tool_id == 2);
    return EXIT_SUCCESS;
}
