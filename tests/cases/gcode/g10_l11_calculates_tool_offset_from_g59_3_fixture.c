#include "support/g10_tool_host.h"
#include "check.h"

int main(void)
{
    prepare_g10_tool();
    char fixture[] = "G10L2P9Z42";
    CHECK(gc_execute_block(fixture) == Status_OK);
    char set[] = "G10L11P3Z2";
    CHECK(gc_execute_block(set) == Status_OK);
    NEAR(g10_tool.offset.z, 40);
    NEAR(g10_tool.offset.x, 0);
    NEAR(g10_tool.offset.y, 0);
    return EXIT_SUCCESS;
}
