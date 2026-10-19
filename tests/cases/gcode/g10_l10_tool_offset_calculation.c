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
    char block2[] = "G10L10P1Z5";
    CHECK(gc_execute_block(block2) == Status_OK);

    return EXIT_SUCCESS;
}
