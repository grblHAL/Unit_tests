#include "support/engine_host.h"
#include "task.h"
#include "check.h"
static unsigned calls[3];
static unsigned due_id, interrupt_id = 1, later_id = 2;
static bool interrupt_pending, interrupt_posted;
static void record(void *data)
{
    CHECK(engine_irq_depth == 0);
    unsigned id = *(unsigned *)data;
    CHECK(id < 3);
    calls[id]++;
}
static void mask_after_pending_interrupt(void)
{
    if(interrupt_pending && engine_irq_depth == 0) {
        interrupt_pending = false;
        CHECK(task_add_delayed(record, &interrupt_id, 0));
        interrupt_posted = true;
    }
    engine_irq_depth++;
}

int main(void)
{
    engine_prepare();
    CHECK(task_add_delayed(record, &due_id, 20));
    CHECK(task_add_delayed(record, &later_id, 30));
    hal.irq_disable = mask_after_pending_interrupt;
    engine_ticks = 20;
    /* A pending driver interrupt runs just before the CPU masks interrupts. */
    interrupt_pending = true;
    engine_execute_tasks(STATE_IDLE);
    CHECK(interrupt_posted && !interrupt_pending);
    CHECK(calls[0] == 1 && calls[1] == 1 && calls[2] == 0);
    CHECK(engine_irq_depth == 0);
    engine_ticks = 30;
    engine_execute_tasks(STATE_IDLE);
    CHECK(calls[0] == 1 && calls[1] == 1 && calls[2] == 1);
    engine_ticks = 100;
    engine_execute_tasks(STATE_IDLE);
    CHECK(calls[0] == 1 && calls[1] == 1 && calls[2] == 1);
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
