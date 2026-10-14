#include "support/engine_host.h"
#include "task.h"
#include "check.h"

static unsigned calls; static int observed[3];
static void record(void *data) { CHECK(calls < 3); observed[calls++] = *(int *)data; }
int main(void)
{
    engine_prepare(); int first = 1, middle = 2, last = 3;
    CHECK(task_add_delayed(record, &last, 30));
    CHECK(task_add_delayed(record, &first, 10));
    CHECK(task_add_delayed(record, &middle, 20));
    task_delete(record, &middle);
    engine_ticks = 30; engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 2 && observed[0] == 1 && observed[1] == 3);
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
