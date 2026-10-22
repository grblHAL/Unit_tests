#include "support/flow_static_macro_host.h"
#include "support/realloc_failure_host.h"
int main(void)
{
    const char *name = "fixture_with_a_long_name_for_workholding_setup_and_tool_checks";
    prepare_static_macro_named(name);
    CHECK(ngc_param_set(1, 99));
    stream_read_ptr previous_read = hal.stream.read;
    char call[128] = "O<";
    strcat(call, name);
    strcat(call, ">CALL[12]");
    fail_realloc = true;
    status_code_t status = gc_execute_block(call);
    fail_realloc = false;
    CHECK(status == Status_FlowControlOutOfMemory && failed_realloc_calls == 1);
    CHECK(hal.stream.file == NULL && hal.stream.read == previous_read);
    CHECK(ngc_call_level() == 0 && file_closes == 0);
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
    CHECK(file_closes == 1 && hal.stream.file == NULL && hal.stream.read == previous_read);
    CHECK(ngc_call_level() == 0);
    CHECK(ngc_param_get(1, &value)); NEAR(value, 99);
    return EXIT_SUCCESS;
}
