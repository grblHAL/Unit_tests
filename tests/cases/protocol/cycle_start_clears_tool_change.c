#include "support/engine_host.h"
#include "protocol.h"
#include "override.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    gc_state.tool_change = true;
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(sys.rt_exec_state == EXEC_CYCLE_START);
    CHECK(!gc_state.tool_change);
    return EXIT_SUCCESS;
}
