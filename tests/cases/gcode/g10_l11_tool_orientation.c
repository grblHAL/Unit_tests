#include "support/incoming_tool_table_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_tool_table();
    char block1[] = "G10L11P1X1Y2Z3Q5R5";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(tools[0].offset.values[Z_AXIS] == -3.0f);
    CHECK(tools[0].offset.values[0] == -1.0f);
    CHECK(tools[0].offset.values[1] == -2.0f);
    CHECK(tools[0].radius == 5.0f);

    CHECK(tools[0].orientation == 5);
    return EXIT_SUCCESS;
}
