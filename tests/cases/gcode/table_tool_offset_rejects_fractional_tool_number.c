#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    grbl.tool_table.n_tools = 1;
    char block[] = "G43H0.5";
    CHECK(gc_execute_block(block) == Status_GcodeCommandValueNotInteger);
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_Cancel);
    return EXIT_SUCCESS;
}
