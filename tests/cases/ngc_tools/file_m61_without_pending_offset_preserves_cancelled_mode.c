#include "support/ngc_tool_file_host.h"
#include "check.h"

int main(void)
{
    vfs_file_t *file = prepare_ngc_tool_file(); CHECK(gc_state.g43_pending == -1);
    char block[] = "M61Q2"; CHECK(gc_execute_block(block) == Status_OK);
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_Cancel);
    for(unsigned axis = 0; axis < 3; axis++) NEAR(gc_state.modal.tool_length_offset[axis], 0);
    stream_redirect_close(file);
    return EXIT_SUCCESS;
}
