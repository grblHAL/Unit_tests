#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    tool_data_t tool = {.tool_id = 3};
    hal.tool.select(&tool, false);
    CHECK(hal.tool.change(&gc_state) == Status_OK);
    CHECK(!gc_state.tool_change);
    CHECK(plan_get_current_block() == NULL);
    CHECK(select_calls == 1 && !selected_next && selected_tool == &tool);
    return EXIT_SUCCESS;
}
