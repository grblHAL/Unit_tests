#include "support/engine_host.h"
#include "sleep.h"
#include "state_machine.h"
#include "check.h"
static unsigned realtime_calls;
static uint16_t free_space = 100;
static uint16_t rx_free(void) { return free_space; }
static void execute(sys_state_t state)
{
    CHECK(state == STATE_IDLE);
    realtime_calls++;
    system_set_exec_state_flag(EXEC_RESET);
}
static void prepare_sleep(void)
{
    engine_parser_prepare();
    state_set(STATE_IDLE);
    engine_ticks = 100;
    hal.stream.get_rx_buffer_free = rx_free;
    grbl.on_execute_realtime = execute;
}

int main(void)
{
    prepare_sleep();
    state_set(STATE_CHECK_MODE);
    gc_state.modal.coolant.flood = true;
    sleep_check();
    CHECK(realtime_calls == 0);
    CHECK(!(sys.rt_exec_state & EXEC_SLEEP));
    return EXIT_SUCCESS;
}
