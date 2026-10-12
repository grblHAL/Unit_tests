#include "support/g10_tool_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_g10_tool();
    state_set(STATE_IDLE);
    char block[] = "G10L10P3Z2E1";
    CHECK(gc_execute_block(block) == Status_GcodeUnusedWords);
    fprintf(stderr, "Rejected G10 L10: X=%g Y=%g Z=%g; expected 1,2,3\n", g10_tool.offset.x, g10_tool.offset.y, g10_tool.offset.z);
    NEAR(g10_tool.offset.x, 1);
    NEAR(g10_tool.offset.y, 2);
    NEAR(g10_tool.offset.z, 3);
    return EXIT_SUCCESS;
}
