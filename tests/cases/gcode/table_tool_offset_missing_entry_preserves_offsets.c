#include "support/tool_offset_host.h"
#include "check.h"

int main(void)
{
    prepare_offset_tool();
    gc_state.modal.tool_length_offset[Z_AXIS] = 12;
    char block[] = "G43H2";
    CHECK(gc_execute_block(block) == Status_GcodeIllegalToolTableEntry);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 12);
    CHECK(gc_state.modal.tool_offset_mode == ToolLengthOffset_Cancel);
    return EXIT_SUCCESS;
}
