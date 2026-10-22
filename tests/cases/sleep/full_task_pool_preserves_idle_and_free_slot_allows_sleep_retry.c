#include "support/engine_host.h"
#include "sleep.h"
#include "task.h"
#include "state_machine.h"
#include "check.h"

static unsigned input_reads, timeout_polls;
static uint16_t rx_free(void) { input_reads++; return 100; }
static void pending_plugin_task(void *data) { (void)data; CHECK(false); }
static void advance_timeout(sys_state_t state)
{
    timeout_polls++;
    engine_ticks += (uint32_t)(SLEEP_DURATION * 60000) + 1;
    engine_execute_tasks(state);
}

int main(void)
{
    engine_parser_prepare();
    state_set(STATE_IDLE);
    engine_ticks = 100;
    hal.stream.get_rx_buffer_free = rx_free;
    grbl.on_execute_realtime = advance_timeout;
    gc_state.modal.coolant.flood = true;
    unsigned contexts[64], count = 0;
    while(count < 64 && task_add_delayed(pending_plugin_task, &contexts[count],
                                      (uint32_t)(SLEEP_DURATION * 60000) + 1000000))
        count++;
    CHECK(count > 0 && count < 64);
    sleep_check();
    CHECK(input_reads == 0 && timeout_polls == 0);
    CHECK(!(sys.rt_exec_state & EXEC_SLEEP) && state_get() == STATE_IDLE);
    task_delete(pending_plugin_task, &contexts[0]);
    engine_ticks += 50;
    sleep_check();
    CHECK(timeout_polls == 1 && input_reads > 0);
    CHECK(sys.rt_exec_state & EXEC_SLEEP);
    for(unsigned i = 1; i < count; i++)
        task_delete(pending_plugin_task, &contexts[i]);
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
