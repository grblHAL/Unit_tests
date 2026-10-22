#include "support/flow_file_host.h"
int main(void)
{
    prepare_flow_file();
    vfs_file_t *file = hal.stream.file;
    stream_read_ptr reader = hal.stream.read;
    CHECK(ngc_param_set(100, 42));
    ngc_string_id_t label = ngc_string_param_set_name("orphan");
    CHECK(label > NGC_MAX_PARAM_ID);
    CHECK(flow_command(label, "SUB") == Status_FlowControlSyntaxError);
    CHECK(hal.stream.file == file && hal.stream.read == reader);
    CHECK(!flow_skip && ngc_call_level() == 0);
    float value;
    CHECK(ngc_param_get(100, &value)); NEAR(value, 42);
    char command[] = "#100=43";
    CHECK(gc_execute_block(command) == Status_OK);
    CHECK(ngc_param_get(100, &value)); NEAR(value, 43);
    ngc_string_param_delete(label);
    close_flow_file();
    return EXIT_SUCCESS;
}
