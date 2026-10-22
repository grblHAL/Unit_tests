#include "support/engine_host.h"
#include "task.h"
#include "check.h"
static unsigned due_calls, retry_calls;
static bool interrupt_pending, interrupt_cancelled;
static void due_work(void *data) { (void)data; due_calls++; }
static void retry_work(void *data) { (void)data; retry_calls++; }
static void mask_after_pending_cancel(void)
{
    if(interrupt_pending && engine_irq_depth == 0) {
        interrupt_pending = false;
        task_delete(retry_work, NULL);
        interrupt_cancelled = true;
    }
    engine_irq_depth++;
}

int main(void)
{
    engine_prepare();
    CHECK(task_add_delayed(due_work, NULL, 10));
    CHECK(task_add_delayed(retry_work, NULL, 20));
    hal.irq_disable = mask_after_pending_cancel;
    engine_ticks = 10;
    interrupt_pending = true;
    engine_execute_tasks(STATE_IDLE);
    CHECK(interrupt_cancelled && !interrupt_pending);
    CHECK(due_calls == 1 && retry_calls == 0 && engine_irq_depth == 0);
    engine_ticks = 100;
    engine_execute_tasks(STATE_IDLE);
    CHECK(due_calls == 1 && retry_calls == 0 && engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
