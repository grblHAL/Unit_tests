#include "support/flow_host.h"
#include "check.h"

int main(void)
{
    prepare_flow();
    CHECK(flow_command(10, "IF[1]") == Status_OK);
    CHECK(flow_command(10, "ERROR[5]") == (status_code_t)5);
    CHECK(!flow_skip);
    CHECK(flow_command(10, "ENDIF") == Status_FlowControlSyntaxError);
    return EXIT_SUCCESS;
}
