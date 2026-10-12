#include "support/g10_tool_host.h"
#include "check.h"

int main(void)
{
    prepare_g10_tool();
    char move[] = "G0Z50";
    CHECK(gc_execute_block(move) == Status_OK);
    char work[] = "G10L2P1Z10";
    CHECK(gc_execute_block(work) == Status_OK);
    char g92[] = "G92Z30";
    CHECK(gc_execute_block(g92) == Status_OK);
    char set[] = "G10L10P3Z2";
    CHECK(gc_execute_block(set) == Status_OK);
    NEAR(g10_tool.offset.z, 28);
    NEAR(g10_tool.offset.x, 0);
    NEAR(g10_tool.offset.y, 0);
    NEAR(gc_state.position[Z_AXIS], 50);
    return EXIT_SUCCESS;
}
