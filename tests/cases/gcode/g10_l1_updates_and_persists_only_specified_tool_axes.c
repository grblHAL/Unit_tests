#include "support/g10_tool_host.h"
#include "check.h"

int main(void)
{
    prepare_g10_tool();
    char block[] = "G10L1P3X10";
    CHECK(gc_execute_block(block) == Status_OK);
    NEAR(g10_tool.offset.x, 10);
    NEAR(g10_tool.offset.y, 2);
    NEAR(g10_tool.offset.z, 3);
    NEAR(g10_tool.radius, 4);
    CHECK(g10_save_calls == 1);
    NEAR(persisted_tool.offset.x, 10);
    NEAR(persisted_tool.offset.y, 2);
    NEAR(gc_state.modal.tool_length_offset[X_AXIS], 0);
    return EXIT_SUCCESS;
}
