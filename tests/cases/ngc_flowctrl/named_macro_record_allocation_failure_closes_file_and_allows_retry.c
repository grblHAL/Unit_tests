#include "support/flow_static_macro_host.h"
static unsigned scoped_calloc_calls, failed_calloc_calls;
static bool inject_record_failure;
void *__real_calloc(size_t count, size_t size);
void *__wrap_calloc(size_t count, size_t size)
{
    // The public call first allocates its redirect context, then its sub record.
    if(inject_record_failure && ++scoped_calloc_calls == 2) {
        failed_calloc_calls++;
        return NULL;
    }
    return __real_calloc(count, size);
}
int main(void)
{
    prepare_static_macro();
    CHECK(ngc_param_set(1, 99));
    stream_read_ptr previous_read = hal.stream.read;
    char call[] = "O<fixture>CALL[12]";
    inject_record_failure = true;
    status_code_t status = gc_execute_block(call);
    inject_record_failure = false;
    CHECK(status == Status_FlowControlOutOfMemory && failed_calloc_calls == 1);
    CHECK(scoped_calloc_calls == 2 && file_closes == 1);
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
