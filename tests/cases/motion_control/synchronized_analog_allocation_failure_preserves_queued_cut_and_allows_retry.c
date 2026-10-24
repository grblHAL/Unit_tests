#include "support/analog_motion_host.h"
#include "support/malloc_failure_host.h"
void *__real_calloc(size_t count, size_t size);
void *__wrap_calloc(size_t count, size_t size)
{
    if(fail_malloc) { failed_malloc_calls++; return NULL; }
    return __real_calloc(count, size);
}
int main(void)
{
    prepare_analog_motion();
    CHECK(io_block("M67E0Q25") == Status_OK);
    queue_motion_program("G1X1F100");
    plan_block_t *queued = plan_get_current_block();
    CHECK(queued && analog_output_calls == 0);
    fail_malloc = true;
    status_code_t status = io_block("M67E1Q50");
    fail_malloc = false;
    CHECK(status == Status_FlowControlOutOfMemory && failed_malloc_calls == 1);
    CHECK(plan_get_current_block() == queued && analog_output_calls == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    CHECK(io_block("M67E1Q50") == Status_OK);
    queue_motion_program("G1X2F100");
    CHECK(analog_output_calls == 0);
    execute_motion_program();
    CHECK(analog_output_calls == 2 && output_calls == 0);
    CHECK(analog_output_port_log[0] == 0 && analog_output_port_log[1] == 1);
    NEAR(analog_output_value_log[0], 25); NEAR(analog_output_value_log[1], 50);
    CHECK(axis_pulses[X_AXIS] == 160 && physical_position[X_AXIS] == 160 && sys.position[X_AXIS] == 160);
    CHECK(plan_get_current_block() == NULL && !sys.abort && sys.alarm == Alarm_None);
    return EXIT_SUCCESS;
}
