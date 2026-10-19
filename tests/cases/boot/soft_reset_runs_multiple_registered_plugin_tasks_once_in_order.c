#include "support/boot_host.h"
#include "task.h"
static unsigned values[] = {1, 2, 3}, observed[3], callbacks;
static bool registered;
static void record_reset_task(void *data)
{
    CHECK(sys.driver_started && !sys.cold_start);
    CHECK(callbacks < 3);
    observed[callbacks++] = *(unsigned *)data;
}
static void register_reset_tasks_after_boot(void)
{
    if(registered) return;
    CHECK(!sys.cold_start);
    for(unsigned i = 0; i < 3; i++) CHECK(task_run_on_reset(record_reset_task, &values[i]));
    CHECK(callbacks == 0);
    registered = true;
}
int main(void)
{
    boot_before_read = register_reset_tasks_after_boot;
    boot_program = "\x18$G\n\x18$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(registered && callbacks == 3);
    CHECK(observed[0] == 1 && observed[1] == 2 && observed[2] == 3);
    CHECK(strstr(engine_output, "error:") == NULL);
    CHECK(boot_setup_calls == 1 && boot_release_calls == 1);
    return EXIT_SUCCESS;
}
