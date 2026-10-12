#include "support/flow_file_host.h"
#include "check.h"

int main(void)
{
    prepare_flow_file();
    vfs_file_t *file = hal.stream.file;
    hal.stream.file = NULL;
    CHECK(flow_command(10, "IF[1]") == Status_OK);
    hal.stream.file = file;
    CHECK(flow_command(20, "IF[1]") == Status_OK);
    ngc_flowctrl_unwind_stack(file);
    CHECK(flow_command(10, "ENDIF") == Status_OK);
    CHECK(!flow_skip);
    close_flow_file();
    return EXIT_SUCCESS;
}
