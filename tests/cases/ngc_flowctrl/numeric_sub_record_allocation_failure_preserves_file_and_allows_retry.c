#include "support/flow_file_host.h"
#include "support/calloc_failure_host.h"

int main(void)
{
    prepare_flow_file();
    vfs_file_t *file = hal.stream.file;
    stream_read_ptr reader = hal.stream.read;
    CHECK(ngc_param_set(100, 42));
    char definition[] = "O10SUB";
    fail_calloc = true;
    status_code_t status = gc_execute_block(definition);
    fail_calloc = false;
    CHECK(status == Status_FlowControlOutOfMemory && failed_calloc_calls == 1);
    CHECK(hal.stream.file == file && hal.stream.read == reader && file_closes == 0);
    CHECK(ngc_call_level() == 0);
    CHECK(gc_execute_block(definition) == Status_OK);
    char skipped[] = "#100=99", end[] = "O10ENDSUB";
    CHECK(gc_execute_block(skipped) == Status_OK);
    CHECK(gc_execute_block(end) == Status_OK);
    float value;
    CHECK(ngc_param_get(100, &value)); NEAR(value, 42);
    char after[] = "#100=43";
    CHECK(gc_execute_block(after) == Status_OK);
    CHECK(ngc_param_get(100, &value)); NEAR(value, 43);
    CHECK(hal.stream.file == file && !sys.abort);
    close_flow_file();
    return EXIT_SUCCESS;
}
