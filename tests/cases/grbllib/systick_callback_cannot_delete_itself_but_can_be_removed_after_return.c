#include "support/engine_host.h"
#include "task.h"
#include "check.h"
static unsigned calls;
static int token;
static void callback(void *data)
{
    CHECK(data == &token); calls++;
    CHECK(!task_delete_systick(callback, data));
}
int main(void)
{
    engine_prepare();
    CHECK(task_add_systick(callback, &token));
    engine_ticks = 1; task_execute(false);
    engine_ticks = 2; task_execute(false);
    CHECK(calls == 2);
    CHECK(task_delete_systick(callback, &token));
    engine_ticks = 3; task_execute(false); CHECK(calls == 2);
    CHECK(engine_irq_depth == 0);
    return EXIT_SUCCESS;
}
