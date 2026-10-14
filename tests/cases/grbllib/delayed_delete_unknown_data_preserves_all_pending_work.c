#include "support/engine_host.h"
#include "task.h"
#include "check.h"

static unsigned calls;
static void record(void *data) { CHECK(data == &calls); calls++; }
int main(void)
{
    engine_prepare(); int unrelated = 0;
    CHECK(task_add_delayed(record, &calls, 10));
    task_delete(record, &unrelated);
    engine_ticks = 10; engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 1 && engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
