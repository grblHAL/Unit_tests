#include "support/flow_file_host.h"
#include "check.h"

int main(void)
{
    prepare_flow_file();
    CHECK(flow_command(10, "CALL[1]") == Status_FlowControlSyntaxError);
    CHECK(!flow_skip);
    CHECK(ngc_call_level() == 0);
    close_flow_file();
    return EXIT_SUCCESS;
}
