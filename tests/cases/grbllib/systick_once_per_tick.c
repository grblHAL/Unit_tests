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
    int data = 7;
    CHECK(task_add_systick(record, &data));
    engine_ticks = 1;
    engine_execute_tasks(STATE_IDLE);
    engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 1);
    engine_ticks = 2;
    engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 2);
    task_delete_systick(record, &data);
    engine_ticks = 3;
    engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 2);
    return EXIT_SUCCESS;
}
