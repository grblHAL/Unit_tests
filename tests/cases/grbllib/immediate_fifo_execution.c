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
    sys.driver_started = true;
    int first = 1, second = 2;
    CHECK(task_add_immediate(record, &first));
    CHECK(task_add_immediate(record, &second));
    engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 2 && order[0] == 1 && order[1] == 2);
    engine_execute_tasks(STATE_IDLE);
    CHECK(calls == 2);
    return EXIT_SUCCESS;
}
