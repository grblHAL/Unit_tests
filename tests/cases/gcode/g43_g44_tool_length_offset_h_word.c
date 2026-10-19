#include "support/incoming_tool_table_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_tool_table();
    tools[0].offset.values[Z_AXIS] = 10.0f;
    char block1[] = "G43H1";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 10.0f);
    char block2[] = "G44H1";
    CHECK(gc_execute_block(block2) == Status_GcodeUnsupportedCommand);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 10.0f);
    char block3[] = "G49";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 0.0f);
    char block4[] = "G43H5";
    CHECK(gc_execute_block(block4) == Status_GcodeIllegalToolTableEntry);

    return EXIT_SUCCESS;
}
