#include "support/ngc_tool_change_host.h"
#include "check.h"

int main(void)
{
    vfs_file_t *file = prepare_ngc_change_file(); ngc_change_status = Status_OK;
    char block[] = "T2M6G43H2"; CHECK(gc_execute_block(block) == Status_OK);
    CHECK(ngc_change_calls == 1); CHECK(ngc_runtime_tool_changes == 1);
    CHECK(gc_state.tool->tool_id == 2); CHECK(gc_state.g43_pending == -1);
    for(unsigned axis = 0; axis < 3; axis++) NEAR(gc_state.modal.tool_length_offset[axis], (float)(axis + 1));
    stream_redirect_close(file);
    return EXIT_SUCCESS;
}
