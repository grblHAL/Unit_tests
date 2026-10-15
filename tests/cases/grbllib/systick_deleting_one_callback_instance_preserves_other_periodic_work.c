#include "support/engine_host.h"
#include "task.h"
#include "check.h"
static unsigned calls[3];
static int tokens[] = {0, 1, 2};
static void callback(void *data) { int index = *(int *)data; CHECK(index >= 0 && index < 3); calls[index]++; }
int main(void)
{
    engine_prepare();
    for(unsigned i = 0; i < 3; i++) CHECK(task_add_systick(callback, &tokens[i]));
    engine_ticks = 1; task_execute(false);
    CHECK(calls[0] == 1 && calls[1] == 1 && calls[2] == 1);
    CHECK(task_delete_systick(callback, &tokens[0]));
    engine_ticks = 2; task_execute(false);
    CHECK(calls[0] == 1 && calls[1] == 2 && calls[2] == 2);
    CHECK(task_delete_systick(callback, &tokens[1]));
    CHECK(task_delete_systick(callback, &tokens[2]));
    CHECK(!task_delete_systick(callback, &tokens[0]));
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
