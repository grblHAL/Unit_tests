#include "support/engine_host.h"
#include "task.h"
#include "check.h"
static unsigned calls;
static int order[4];
static void record(void *data)
{
    CHECK(calls < 4);
    order[calls++] = *(int *)data;
}

int main(void)
{
    engine_prepare();
    int first = 1, second = 2;
    CHECK(task_add_delayed(record, &second, 20));
    CHECK(task_add_delayed(record, &first, 10));
    engine_ticks = 9;
    engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 0);
    engine_ticks = 10;
    engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 1 && order[0] == 1);
    engine_ticks = 20;
    engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 2 && order[1] == 2);
    return EXIT_SUCCESS;
}
