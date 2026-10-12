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
    int data = 7;
    sys.driver_started = true;
    CHECK(task_run_on_reset(record, &data));
    task_execute_on_startup();
    CHECK(calls == 1 && order[0] == 7);
    task_execute_on_startup();
    CHECK(calls == 1);
    return EXIT_SUCCESS;
}
