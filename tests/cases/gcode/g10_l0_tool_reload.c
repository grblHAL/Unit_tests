#include "support/incoming_tool_table_host.h"
#include "check.h"
#include <string.h>

static status_code_t tool_reload(void)
{

    return Status_OK;
}
int main(void)
{
    prepare_incoming_tool_table();
    grbl.tool_table.reload = tool_reload;
    char block1[] = "G10L0P1";
    CHECK(gc_execute_block(block1) == Status_OK);
    char block2[] = "G10L1P5R1";
    CHECK(gc_execute_block(block2) == Status_GcodeIllegalToolTableEntry);

    return EXIT_SUCCESS;
}
