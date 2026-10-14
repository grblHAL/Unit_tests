#include "support/engine_host.h"
#include "task.h"
#include "check.h"

static unsigned calls;
static void record(void *data)
{
    CHECK(data == &calls); calls++;
    if(calls == 1) CHECK(task_add_delayed(record, data, 5));
}
int main(void)
{
    engine_prepare(); CHECK(task_add_delayed(record, &calls, 10));
    engine_ticks = 10; engine_execute_tasks(STATE_IDLE); CHECK(calls == 1);
    engine_ticks = 14; engine_execute_tasks(STATE_IDLE); CHECK(calls == 1);
    engine_ticks = 15; engine_execute_tasks(STATE_IDLE); CHECK(calls == 2);
    engine_ticks = 30; engine_execute_tasks(STATE_IDLE); CHECK(calls == 2);
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
