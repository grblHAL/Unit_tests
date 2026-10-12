#include "support/engine_host.h"
#include "task.h"
#include "check.h"
void task_execute_on_startup(void);
static unsigned calls;
static int order[8];
static void record(void *data)
{
    CHECK(calls < 8);
    order[calls++] = *(int *)data;
}

int main(void)
{
    engine_prepare();
    int first = 1, second = 2;
    sys.cold_start = true;
    sys.driver_started = true;
    CHECK(task_run_on_startup(record, &first));
    CHECK(task_run_on_startup(record, &second));
    CHECK(calls == 0);
    task_execute_on_startup();
    CHECK(calls == 2);
    CHECK(order[0] == 1 && order[1] == 2);
    task_execute_on_startup();
    CHECK(calls == 2);
    return EXIT_SUCCESS;
}
