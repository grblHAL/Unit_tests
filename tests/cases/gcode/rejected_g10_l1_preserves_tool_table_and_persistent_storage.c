#include "support/g10_tool_host.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    prepare_g10_tool();
    state_set(STATE_IDLE);
    char block[] = "G10L1P3X10E1";
    CHECK(gc_execute_block(block) == Status_GcodeUnusedWords);
    fprintf(stderr, "Rejected G10: tool X=%g expected=1; persistence callbacks=%u expected=0\n", g10_tool.offset.x, g10_save_calls);
    NEAR(g10_tool.offset.x, 1);
    CHECK(g10_save_calls == 0);
    return EXIT_SUCCESS;
}
