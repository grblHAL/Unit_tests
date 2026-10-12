#include "support/engine_host.h"
#include "task.h"
#include "check.h"
void task_execute_on_startup(void);
static void noop(void *data) { (void)data; }
int main(void)
{
    engine_prepare();
    sys.cold_start = true;
    sys.driver_started = true;
    for(unsigned i = 0; i < 40; i++) CHECK(task_run_on_startup(noop, NULL));
    CHECK(!task_run_on_startup(noop, NULL));
    task_execute_on_startup();
    for(unsigned i = 0; i < 40; i++) CHECK(task_run_on_startup(noop, NULL));
    CHECK(!task_run_on_startup(noop, NULL));
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
