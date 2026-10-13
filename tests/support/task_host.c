/* Keep the scheduler implementation upstream-owned; this wrapper only exposes
   a test entry point in the same translation unit. */
#include "../../core/grbllib.c"
void engine_execute_tasks(sys_state_t state)
{
    /* Legacy core accepts a state; current core accepts a wait flag.
       Execute foreground work without entering its blocking delay hook. */
    task_execute(_Generic(&task_execute, void (*)(bool): false, default: state));
}
