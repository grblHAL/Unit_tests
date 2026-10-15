#include "support/tool_change_host.h"

int main(void)
{
    prepare_tool_change();
    install_manual_change_interface();
    sys.homed.mask = 0;
    char change[] = "T3M6";
    CHECK(gc_execute_block(change) == Status_HomingRequired);
    CHECK(!gc_state.tool_change && state_get() == STATE_IDLE);
    CHECK(plan_get_current_block() == NULL && wake_calls == 0);
    return EXIT_SUCCESS;
}
