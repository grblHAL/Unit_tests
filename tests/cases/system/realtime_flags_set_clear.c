#include "support/engine_host.h"
#include "report.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    sys.rt_exec_state = 0;
    system_set_exec_state_flag(EXEC_FEED_HOLD);
    system_set_exec_state_flag(EXEC_CYCLE_START);
    CHECK(sys.rt_exec_state == (EXEC_FEED_HOLD | EXEC_CYCLE_START));
    system_clear_exec_state_flag(EXEC_FEED_HOLD);
    CHECK(sys.rt_exec_state == EXEC_CYCLE_START);
    system_clear_exec_states();
    CHECK(sys.rt_exec_state == 0);
    return EXIT_SUCCESS;
}
