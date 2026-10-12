#include "support/engine_host.h"
#include "task.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    CHECK(!task_add_immediate(NULL, NULL));
    CHECK(!task_add_delayed(NULL, NULL, 1));
    CHECK(!task_add_systick(NULL, NULL));
    CHECK(!task_run_on_reset(NULL, NULL));
    sys.cold_start = true;
    CHECK(!task_run_on_startup(NULL, NULL));
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
