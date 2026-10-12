#include "support/flow_file_host.h"
#include "check.h"

int main(void)
{
    prepare_flow_file();
    CHECK(flow_command(10, "IF[1]") == Status_OK);
    CHECK(flow_command(20, "IF[1]") == Status_OK);
    ngc_flowctrl_unwind_stack(hal.stream.file);
    CHECK(flow_command(20, "ENDIF") == Status_FlowControlSyntaxError);
    CHECK(flow_command(30, "IF[1]") == Status_OK);
    CHECK(flow_command(30, "ENDIF") == Status_OK);
    close_flow_file();
    return EXIT_SUCCESS;
}
