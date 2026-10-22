#include "support/flow_static_macro_host.h"
static bool fail_next_malloc;
static unsigned failed_malloc_calls;
void *__real_malloc(size_t size);
void *__wrap_malloc(size_t size)
{
    if(fail_next_malloc) {
        fail_next_malloc = false;
        failed_malloc_calls++;
        return NULL;
    }
    return __real_malloc(size);
}
static void arm_argument_failure(void) { fail_next_malloc = true; }
int main(void)
{
    prepare_static_macro();
    CHECK(ngc_param_set(1, 99));
    stream_read_ptr previous_read = hal.stream.read;
    char call[] = "O<fixture>CALL[12]";
    static_macro_on_open = arm_argument_failure;
    status_code_t status = gc_execute_block(call);
    static_macro_on_open = NULL;
    fail_next_malloc = false;
    CHECK(status == Status_FlowControlOutOfMemory && failed_malloc_calls == 1);
    CHECK(file_closes == 1);
    CHECK(hal.stream.file == NULL && hal.stream.read == previous_read);
    CHECK(ngc_call_level() == 0);
    float value;
    CHECK(ngc_param_get(1, &value)); NEAR(value, 99);
    CHECK(gc_execute_block(call) == Status_OK);
    CHECK(hal.stream.file != NULL && ngc_call_level() == 1);
    CHECK(ngc_param_get(1, &value)); NEAR(value, 12);
    const char *body = "G21\n";
    for(unsigned i = 0; body[i]; i++) CHECK(hal.stream.read() == body[i]);
    char units[] = "G21";
    CHECK(gc_execute_block(units) == Status_OK);
    CHECK(grbl.report.status_message(Status_OK) == Status_OK);
    CHECK(hal.stream.read() == ASCII_EOF);
    CHECK(grbl.on_file_end(hal.stream.file, Status_OK) == Status_OK);
    CHECK(file_closes == 2 && hal.stream.file == NULL && hal.stream.read == previous_read);
    CHECK(ngc_call_level() == 0);
    CHECK(ngc_param_get(1, &value)); NEAR(value, 99);
    return EXIT_SUCCESS;
}
