#include "support/io_motion_host.h"
#include "support/malloc_failure_host.h"
void *__real_calloc(size_t count, size_t size);
void *__wrap_calloc(size_t count, size_t size)
{
    if(fail_malloc) { failed_malloc_calls++; return NULL; }
    return __real_calloc(count, size);
}

int main(void)
{
    prepare_io_motion();
    CHECK(io_block("M62P0") == Status_OK);
    queue_motion_program("G1X1F100");
    plan_block_t *queued = plan_get_current_block();
    CHECK(queued != NULL && output_calls == 0);
    fail_malloc = true;
    status_code_t status = io_block("M62P1");
    fail_malloc = false;
    CHECK(failed_malloc_calls == 1);
    CHECK(plan_get_current_block() == queued && output_calls == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(axis_pulses[axis] == 0 && physical_position[axis] == 0);
    CHECK(io_block("M62P1") == Status_OK);
    queue_motion_program("G1X2F100");
    CHECK(output_calls == 0);
    execute_motion_program();
    CHECK(output_calls == 2);
    CHECK(output_pin_log[0] == 0 && output_log[0]);
    CHECK(output_pin_log[1] == 1 && output_log[1]);
    CHECK(sys.position[X_AXIS] == 160 && physical_position[X_AXIS] == 160);
    CHECK(axis_pulses[X_AXIS] == 160 && plan_get_current_block() == NULL);
    CHECK(!sys.abort && sys.alarm == Alarm_None);
    fprintf(stderr, "Synchronized output allocation: status=%u failures=%u retry_outputs=%u X_steps=%u\n",
        (unsigned)status, failed_malloc_calls, output_calls, axis_pulses[X_AXIS]);
    CHECK(status != Status_OK);
    return EXIT_SUCCESS;
}
