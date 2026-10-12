#include "support/ngc_tool_file_host.h"
#include "check.h"

int main(void)
{
    vfs_file_t *file = prepare_ngc_tool_file(); gc_state.g43_pending = 2;
    tool_id_t current = gc_state.tool->tool_id, pending = gc_state.tool_pending;
    char block[] = "M61Q1.5"; CHECK(gc_execute_block(block) == Status_GcodeCommandValueNotInteger);
    CHECK(gc_state.g43_pending == -1); CHECK(gc_state.tool->tool_id == current);
    CHECK(gc_state.tool_pending == pending); CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_Cancel);
    stream_redirect_close(file);
    return EXIT_SUCCESS;
}
