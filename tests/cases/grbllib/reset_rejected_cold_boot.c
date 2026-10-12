#include "support/engine_host.h"
#include "task.h"
#include "check.h"
void task_execute_on_startup(void);
static void noop(void *data) { (void)data; }
int main(void)
{
    engine_prepare();
    sys.cold_start = true;
    CHECK(!task_run_on_reset(noop, NULL));
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
