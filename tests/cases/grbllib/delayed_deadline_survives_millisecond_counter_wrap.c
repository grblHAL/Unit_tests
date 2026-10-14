#include "support/engine_host.h"
#include "task.h"
#include "check.h"

static unsigned calls;
static void record(void *data) { CHECK(data == &calls); calls++; }
int main(void)
{
    engine_prepare(); engine_ticks = UINT32_MAX - 5;
    CHECK(task_add_delayed(record, &calls, 10));
    engine_ticks = UINT32_MAX - 1; engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 0);
    engine_ticks = 3; engine_execute_tasks(STATE_IDLE); CHECK(calls == 0);
    engine_ticks = 4; engine_execute_tasks(STATE_IDLE); CHECK(calls == 1);
    engine_ticks = 5; engine_execute_tasks(STATE_IDLE); CHECK(calls == 1);
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
