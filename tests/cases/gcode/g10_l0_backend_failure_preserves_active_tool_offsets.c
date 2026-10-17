#include "support/tool_reload_host.h"
int main(void)
{
    prepare_tool_reload();
    CHECK(m6_block("G43.1Z5") == Status_OK);
    tool_reload_status = Status_SettingReadFail;
    CHECK(m6_block("G10L0") == Status_SettingReadFail);
    CHECK(tool_reload_calls == 1 && gc_state.tool->tool_id == 0);
    CHECK(gc_state.modal.tool_length_offset[Z_AXIS] == 5);
    CHECK(gc_state.position[X_AXIS] == 0 && gc_state.position[Z_AXIS] == 0);
    CHECK(m6_change_calls == 0 && m6_select_calls == 0);
    tool_reload_status = Status_OK;
    CHECK(m6_block("G10L0") == Status_OK);
    CHECK(tool_reload_calls == 2);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], gc_state.tool->offset.z);
    return EXIT_SUCCESS;
}
