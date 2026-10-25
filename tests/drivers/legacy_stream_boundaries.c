#include "grbl/hal.h"
#include "grbl/task.h"
#include "check.h"
sys_state_t state_get(void) { return STATE_IDLE; }
void dummy_handler(void) { CHECK(false); }
void report_message(const char *text, message_type_t type)
{
    (void)text;
    (void)type;
    CHECK(false);
}
void system_add_rt_report(report_tracking_t report)
{
    (void)report;
    CHECK(false);
}
bool task_add_immediate(foreground_task_ptr fn, void *data)
{
    (void)fn;
    (void)data;
    CHECK(false);
    return false;
}
bool task_add_delayed(foreground_task_ptr fn, void *data, uint32_t ms)
{
    (void)fn;
    (void)data;
    (void)ms;
    CHECK(false);
    return false;
}
