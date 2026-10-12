#include "support/engine_host.h"
#include "task.h"
#include "check.h"
void task_execute_on_startup(void);
static void noop(void *data) { (void)data; }
int main(void)
{
    engine_prepare();
    int data[40];
    for(unsigned i = 0; i < 40; i++) CHECK(task_add_systick(noop, &data[i]));
    CHECK(!task_add_systick(noop, NULL));
    task_delete_systick(noop, &data[20]);
    CHECK(task_add_systick(noop, NULL));
    CHECK(!task_add_systick(noop, NULL));
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
