#include "support/debug_serial_host.h"
#include "task.h"
static unsigned pending = 3, polls, tasks_run;
static uint16_t pending_output(void)
{
    polls++;
    return pending ? pending-- : 0;
}
static void foreground(void *data)
{
    CHECK(data == &tasks_run);
    CHECK(pending < 3);
    tasks_run++;
}
int main(void)
{
    start_debug_serial();
    sys.driver_started = true;
    hal.debug.get_tx_buffer_count = pending_output;
    CHECK(task_add_immediate(foreground, &tasks_run));
    debug_write("alarm report");
    CHECK(strcmp(debug_output, "alarm report") == 0);
    CHECK(polls == 4 && pending == 0 && tasks_run == 1);
    return EXIT_SUCCESS;
}
