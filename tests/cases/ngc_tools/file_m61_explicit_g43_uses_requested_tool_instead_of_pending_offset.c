#include "support/ngc_tool_file_host.h"
#include "check.h"

int main(void)
{
    vfs_file_t *file = prepare_ngc_tool_file(); gc_state.g43_pending = 2;
    tool_data_t tool = {.tool_id = 1, .offset.values = {4, 5, 6}}; CHECK(host_save_tool(&tool));
    char block[] = "M61Q2G43H1"; CHECK(gc_execute_block(block) == Status_OK);
    CHECK(gc_state.g43_pending == -1); CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_Enable);
    for(unsigned axis = 0; axis < 3; axis++) NEAR(gc_state.modal.tool_length_offset[axis], (float)(axis + 4));
    stream_redirect_close(file);
    return EXIT_SUCCESS;
}
