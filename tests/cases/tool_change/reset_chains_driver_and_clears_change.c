#include "support/tool_change_host.h"
#include "check.h"

int main(void)
{
    prepare_tool_change();
    gc_state.tool_change = true;
    hal.driver_reset();
    CHECK(reset_calls == 1);
    CHECK(!gc_state.tool_change);
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
