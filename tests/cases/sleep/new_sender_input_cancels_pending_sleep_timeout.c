#include "support/sleep_wait_host.h"
int main(void)
{
    prepare_sleep_workflow();
    sleep_input_arrives = true;
    wait_for_sleep();
    CHECK(sleep_wait_calls == 1);
    CHECK(!(sys.rt_exec_state & EXEC_SLEEP));
    CHECK(sleep_free_space == 99);
    grbl.on_execute_realtime = protocol_execute_noop;
    engine_ticks += (uint32_t)(SLEEP_DURATION * 60000) + 1;
    engine_execute_tasks(STATE_IDLE);
    CHECK(!(sys.rt_exec_state & EXEC_SLEEP));
    CHECK(state_get() == STATE_IDLE);
    return EXIT_SUCCESS;
}
