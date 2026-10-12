#include "support/ngc_tool_file_host.h"
#include "check.h"

int main(void)
{
    vfs_file_t *file = prepare_ngc_tool_file(); gc_state.g43_pending = 2;
    char block[] = "M61Q2G49"; CHECK(gc_execute_block(block) == Status_OK);
    CHECK(gc_state.g43_pending == -1); CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_Cancel);
    for(unsigned axis = 0; axis < 3; axis++) NEAR(gc_state.modal.tool_length_offset[axis], 0);
    stream_redirect_close(file); CHECK(file_closes == 1);
    return EXIT_SUCCESS;
}
