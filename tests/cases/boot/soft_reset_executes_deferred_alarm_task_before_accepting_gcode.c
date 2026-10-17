#include "support/boot_host.h"
#include "task.h"
static bool registered;
static void register_alarm_after_boot(void)
{
    if(registered) return;
    CHECK(!sys.cold_start);
    CHECK(task_run_on_reset(task_raise_alarm, (void *)(uintptr_t)Alarm_HomingRequired));
    registered = true;
}
int main(void)
{
    boot_before_read = register_alarm_after_boot;
    boot_program = "\x18G91\n";
    CHECK(grbl_enter() == 0);
    CHECK(registered);
    CHECK(sys.alarm == Alarm_HomingRequired);
    CHECK(strstr(engine_output, "ALARM:11") != NULL);
    CHECK(strstr(engine_output, "error:9") != NULL);
    CHECK(!gc_state.modal.distance_incremental);
    return EXIT_SUCCESS;
}
