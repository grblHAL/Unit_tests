#include "support/engine_host.h"
#include "task.h"
#include "check.h"
static unsigned due_calls, later_calls;
static bool interrupt_pending, interrupt_cancelled;
static void due_work(void *data) { (void)data; due_calls++; }
static void later_work(void *data) { (void)data; later_calls++; }
static void mask_after_pending_cancel(void)
{
    if(interrupt_pending && engine_irq_depth == 0) {
        interrupt_pending = false;
        task_delete(due_work, NULL);
        interrupt_cancelled = true;
    }
    engine_irq_depth++;
}

int main(void)
{
    engine_prepare();
    CHECK(task_add_delayed(due_work, NULL, 10));
    CHECK(task_add_delayed(later_work, NULL, 20));
    hal.irq_disable = mask_after_pending_cancel;
    engine_ticks = 10;
    /* Driver cancels an outstanding timer before the foreground masks IRQs. */
    interrupt_pending = true;
    engine_execute_tasks(STATE_IDLE);
    CHECK(interrupt_cancelled && !interrupt_pending);
    CHECK(due_calls == 0 && later_calls == 0 && engine_irq_depth == 0);
    engine_ticks = 20;
    engine_execute_tasks(STATE_IDLE);
    CHECK(due_calls == 0 && later_calls == 1);
    engine_ticks = 100;
    engine_execute_tasks(STATE_IDLE);
    CHECK(due_calls == 0 && later_calls == 1 && engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
