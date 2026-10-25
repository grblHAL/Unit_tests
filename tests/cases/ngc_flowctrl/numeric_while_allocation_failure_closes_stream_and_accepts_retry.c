#include "support/flow_program_host.h"
#include "state_machine.h"
static bool fail_expression;
static unsigned failed_allocations, arm_calls;
void *__real_malloc(size_t size);
void *__wrap_malloc(size_t size)
{
    if(fail_expression) {
        CHECK(size == strlen("[1]") + 1);
        fail_expression = false;
        failed_allocations++;
        return NULL;
    }
    return __real_malloc(size);
}
static status_code_t arm_expression_failure(char *text)
{
    CHECK(strcmp(text, "Arm while") == 0);
    arm_calls++;
    fail_expression = true;
    return Status_OK;
}
static status_code_t read_numeric_program(void)
{
    char block[96];
    unsigned length = 0;
    for(unsigned reads = 0; reads < 10000; reads++) {
        int32_t c = hal.stream.read();
        if(c == SERIAL_NO_DATA) continue;
        if(c == ASCII_EOF) return Status_OK;
        if(c == ASCII_LF) {
            block[length] = '\0';
            status_code_t status = gc_execute_block(block);
            if(status != Status_OK) return status;
            length = 0;
        } else {
            CHECK(length + 1 < sizeof(block));
            block[length++] = (char)c;
        }
    }
    fprintf(stderr, "numeric bound: failures=%u arms=%u closes=%u pos=%zu text=%s param=%g file=%p\n", failed_allocations, arm_calls, file_closes, file_position, file_text, (double)flow_program_parameter(100), (void *)hal.stream.file);
    CHECK(false);
    return Status_FlowControlSyntaxError;
}
int main(void)
{
    prepare_file_stream("#100=0\n(Arm while)\nO10WHILE[1]\n#100=99\nO10ENDWHILE\n");
    ngc_flowctrl_init();
    state_set(STATE_IDLE);
    grbl.on_gcode_comment = arm_expression_failure;
    CHECK(stream_redirect_read("/fixture/program", NULL, NULL) != NULL);
    CHECK(read_numeric_program() == Status_FlowControlOutOfMemory);
    CHECK(failed_allocations == 1 && arm_calls == 1 && !fail_expression);
    CHECK(ngc_call_level() == 0 && !gc_state.skip_blocks);
    NEAR(flow_program_parameter(100), 0);
    stream_redirect_close(hal.stream.file);
    CHECK(file_closes == 1 && hal.stream.file == NULL);
    file_text = "O10WHILE[#100LT2]\n#100=[#100+1]\nO10ENDWHILE\n";
    CHECK(stream_redirect_read("/fixture/program", NULL, NULL) != NULL);
    CHECK(read_numeric_program() == Status_OK);
    CHECK(ngc_call_level() == 0 && !gc_state.skip_blocks);
    NEAR(flow_program_parameter(100), 2);
    stream_redirect_close(hal.stream.file);
    CHECK(file_closes == 2 && hal.stream.file == NULL);
    CHECK(failed_allocations == 1 && arm_calls == 1);
    return EXIT_SUCCESS;
}
