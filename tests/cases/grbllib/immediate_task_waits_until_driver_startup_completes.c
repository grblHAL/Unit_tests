#include "support/engine_host.h"
#include "task.h"
#include "check.h"

static unsigned calls;
static void record(void *data) { CHECK(data == &calls); calls++; }
int main(void)
{
    engine_prepare(); sys.driver_started = false;
    CHECK(task_add_immediate(record, &calls));
    engine_execute_tasks(STATE_IDLE); CHECK(calls == 0);
    sys.driver_started = true;
    engine_execute_tasks(STATE_IDLE); CHECK(calls == 1);
    engine_execute_tasks(STATE_IDLE); CHECK(calls == 1);
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
