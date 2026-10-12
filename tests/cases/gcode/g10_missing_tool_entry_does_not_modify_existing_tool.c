#include "support/g10_tool_host.h"
#include "check.h"

int main(void)
{
    prepare_g10_tool();
    char block[] = "G10L1P4X10";
    CHECK(gc_execute_block(block) == Status_GcodeIllegalToolTableEntry);
    NEAR(g10_tool.offset.x, 1);
    NEAR(g10_tool.radius, 4);
    CHECK(g10_save_calls == 0);
    return EXIT_SUCCESS;
}
