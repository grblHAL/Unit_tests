#include "support/engine_host.h"
#include "task.h"
#include "check.h"
static int event_id = 1, retry_id = 2, other_id = 3;
static unsigned calls;
static int observed[4];
static void record(void *data)
{
    CHECK(calls < 4);
    observed[calls++] = *(int *)data;
    if(data == &event_id) {
        task_delete(record, &retry_id);
        CHECK(task_add_delayed(record, &retry_id, 5));
    }
}
int main(void)
{
    engine_prepare();
    CHECK(task_add_delayed(record, &event_id, 10));
    CHECK(task_add_delayed(record, &retry_id, 20));
    CHECK(task_add_delayed(record, &other_id, 30));
    engine_ticks = 30;
    engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 2 && observed[0] == 1 && observed[1] == 3);
    engine_ticks = 34;
    engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 2);
    engine_ticks = 35;
    engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 3 && observed[2] == 2);
    engine_ticks = 100;
    engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 3 && engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
