#include "support/engine_host.h"
#include "task.h"
#include "check.h"
static unsigned calls;
static int order[4], values[] = {0, 1, 2, 3};
static void record(void *data)
{
    CHECK(calls < 4); int value = *(int *)data; order[calls++] = value;
    if(value == 0) CHECK(task_add_immediate(record, &values[3]));
}
int main(void)
{
    engine_prepare(); sys.driver_started = true;
    for(unsigned i = 0; i < 3; i++) CHECK(task_add_immediate(record, &values[i]));
    task_execute(false);
    CHECK(calls == 3 && order[0] == 0 && order[1] == 1 && order[2] == 2);
    task_execute(false); CHECK(calls == 4 && order[3] == 3);
    task_execute(false); CHECK(calls == 4);
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
