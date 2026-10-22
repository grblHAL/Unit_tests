#include "support/m6_program_host.h"

static void select_and_stop_spindle(tool_data_t *tool)
{
    m6_selected(tool);
    CHECK(gc_spindle_get(0)->state.on);
    gc_spindle_off();
}

int main(void)
{
    prepare_m6_program();
    CHECK(m6_block("M3S500") == Status_OK);
    CHECK(gc_spindle_get(0)->state.on);
    grbl.on_tool_selected = select_and_stop_spindle;
    CHECK(m6_block("T1M6") == Status_OK);
    CHECK(m6_selected_calls == 1 && m6_changed_calls == 1);
    CHECK(gc_state.tool == &offset_tool);
    CHECK(!gc_spindle_get(0)->state.on);
    CHECK(m6_block("M3S600") == Status_OK);
    CHECK(gc_spindle_get(0)->state.on);
    CHECK(gc_spindle_get(0)->rpm == 600.0f);
    CHECK(m6_block("M5") == Status_OK);
    CHECK(!gc_spindle_get(0)->state.on);
    return EXIT_SUCCESS;
}
