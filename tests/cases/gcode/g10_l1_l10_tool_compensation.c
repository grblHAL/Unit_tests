#include "support/incoming_tool_table_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_tool_table();
    char block1[] = "G10L1P1R5";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(tools[0].radius == 5.0f);
    char block2[] = "G10L10P1R3";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(tools[0].radius == 3.0f);
    char block3[] = "G10L1P1R5Z10";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(tools[0].radius == 5.0f);
    CHECK(tools[0].offset.values[Z_AXIS] == 10.0f);
    char block4[] = "G10L1P5R5";
    CHECK(gc_execute_block(block4) == Status_GcodeIllegalToolTableEntry);

    return EXIT_SUCCESS;
}
