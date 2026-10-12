#include "support/ngc_tool_runtime_host.h"
#include "check.h"
static unsigned selected_calls;
static void record_selected(tool_data_t *tool) { CHECK(tool->tool_id == 2); selected_calls++; }
int main(void)
{
    vfs_file_t *file = prepare_ngc_runtime_file(); grbl.on_tool_selected = record_selected;
    char first[] = "M61Q2", second[] = "M61Q2";
    CHECK(gc_execute_block(first) == Status_OK); CHECK(selected_calls == 1);
    CHECK(gc_execute_block(second) == Status_OK); CHECK(selected_calls == 2);
    CHECK(gc_state.tool->tool_id == 2); stream_redirect_close(file);
    return EXIT_SUCCESS;
}
