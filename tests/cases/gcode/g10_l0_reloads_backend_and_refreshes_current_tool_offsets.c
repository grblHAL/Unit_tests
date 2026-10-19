#include "support/tool_reload_host.h"
int main(void)
{
    prepare_tool_reload();
    CHECK(m6_block("G43.1Z5") == Status_OK);
    CHECK(gc_state.modal.tool_length_offset[Z_AXIS] == 5);
    CHECK(m6_block("G10L0") == Status_OK);
    CHECK(tool_reload_calls == 1 && gc_state.tool->tool_id == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        NEAR(gc_state.modal.tool_length_offset[axis], gc_state.tool->offset.values[axis]);
        CHECK(gc_state.position[axis] == 0);
    }
    CHECK(m6_change_calls == 0 && m6_select_calls == 0);
    return EXIT_SUCCESS;
}
