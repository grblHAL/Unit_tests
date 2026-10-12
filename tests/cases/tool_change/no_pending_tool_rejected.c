#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    CHECK(hal.tool.change(&gc_state) == Status_GCodeToolError);
    CHECK(!gc_state.tool_change);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
