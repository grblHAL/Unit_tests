#include "support/engine_host.h"
#include "sleep.h"
#include "state_machine.h"
#include "check.h"
static unsigned calls;
static uint16_t rx_free(void) { return 100; }
static void advance_scheduler(sys_state_t state)
{
    calls++;
    engine_ticks += (uint32_t)(SLEEP_DURATION * 60000) + 1;
    engine_execute_tasks(state);
}
int main(void)
{
    engine_parser_prepare();
    state_set(STATE_IDLE);
    engine_ticks = 100;
    hal.stream.get_rx_buffer_free = rx_free;
    grbl.on_execute_realtime = advance_scheduler;
    gc_state.modal.coolant.flood = true;
    sleep_check();
    CHECK(calls == 1);
    CHECK(sys.rt_exec_state & EXEC_SLEEP);
    return EXIT_SUCCESS;
}
