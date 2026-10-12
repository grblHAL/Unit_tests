#include "support/flow_host.h"
#include "check.h"

int main(void)
{
    prepare_flow();
    for(uint32_t label = 1; label <= 20; label++)
        CHECK(flow_command(label, "IF[1]") == Status_OK);
    CHECK(flow_command(21, "IF[1]") == Status_FlowControlStackOverflow);
    CHECK(!flow_skip);
    CHECK(flow_command(1, "ENDIF") == Status_FlowControlSyntaxError);
    CHECK(flow_command(30, "IF[1]") == Status_OK);
    CHECK(flow_command(30, "ENDIF") == Status_OK);
    return EXIT_SUCCESS;
}
