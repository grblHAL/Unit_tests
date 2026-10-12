#include "support/g10_tool_host.h"
#include "check.h"

int main(void)
{
    prepare_g10_tool();
    char block[] = "G20G10L1P3R0.5";
    CHECK(gc_execute_block(block) == Status_OK);
    NEAR(g10_tool.radius, 12.7f);
    NEAR(g10_tool.offset.x, 1);
    NEAR(g10_tool.offset.y, 2);
    NEAR(g10_tool.offset.z, 3);
    CHECK(g10_save_calls == 1);
    NEAR(persisted_tool.radius, 12.7f);
    return EXIT_SUCCESS;
}
