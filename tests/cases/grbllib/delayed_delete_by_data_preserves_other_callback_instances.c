#include "support/engine_host.h"
#include "task.h"
#include "check.h"

static unsigned calls; static int observed;
static void record(void *data) { calls++; observed = *(int *)data; }
int main(void)
{
    engine_prepare(); int first = 11, second = 22;
    CHECK(task_add_delayed(record, &first, 10));
    CHECK(task_add_delayed(record, &second, 20));
    task_delete(record, &first);
    engine_ticks = 10; engine_execute_tasks(STATE_IDLE); CHECK(calls == 0);
    engine_ticks = 20; engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 1 && observed == 22);
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
