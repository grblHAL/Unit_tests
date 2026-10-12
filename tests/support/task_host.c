/* Keep the scheduler implementation upstream-owned; this wrapper only exposes
   a test entry point in the same translation unit. */
#include "../../core/grbllib.c"
void engine_execute_tasks(sys_state_t state)
{
    task_execute(state);
}
