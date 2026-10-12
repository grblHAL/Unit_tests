#include "support/flow_host.h"
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    prepare_flow();
    CHECK(ngc_param_set(1, 2));
    CHECK(flow_command(10, "IF[1]") == Status_OK);
    CHECK(flow_command(10, "ERROR[#1+3]") == Status_HomingDisabled);
    CHECK(!flow_skip);
    CHECK(flow_command(10, "ENDIF") == Status_FlowControlSyntaxError);
    return EXIT_SUCCESS;
}
