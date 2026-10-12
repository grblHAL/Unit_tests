#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    grbl.tool_table.n_tools = 0;
    char block[] = "G10L1P3X10";
    CHECK(gc_execute_block(block) == Status_GcodeUnsupportedCommand);
    NEAR(gc_state.modal.tool_length_offset[X_AXIS], 0);
    return EXIT_SUCCESS;
}
