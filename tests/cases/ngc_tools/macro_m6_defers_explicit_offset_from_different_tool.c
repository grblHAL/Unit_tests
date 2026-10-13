#include "support/ngc_tool_change_host.h"
#include "check.h"

int main(void)
{
    vfs_file_t *file = prepare_ngc_change_file();
    tool_data_t offset = {.tool_id = 3, .offset.values = {4, 5, 6}}; CHECK(host_save_tool(&offset));
    char block[] = "T2M6G43H3"; CHECK(gc_execute_block(block) == Status_OK);
    CHECK(gc_state.g43_pending == 3); CHECK(gc_state.tool->tool_id == 0);
    char complete[] = "M61Q2"; CHECK(gc_execute_block(complete) == Status_OK); CHECK(gc_state.tool->tool_id == 2); CHECK(gc_state.g43_pending == -1);
    for(unsigned axis = 0; axis < 3; axis++) NEAR(gc_state.modal.tool_length_offset[axis], (float)(axis + 4));
    stream_redirect_close(file);
    return EXIT_SUCCESS;
}
