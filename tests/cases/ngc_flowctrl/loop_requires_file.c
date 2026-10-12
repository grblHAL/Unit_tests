#include "support/flow_host.h"
#include "check.h"

int main(void)
{
    prepare_flow();
    CHECK(flow_command(10, "WHILE[1]") == Status_FlowControlNotExecutingMacro);
    CHECK(!flow_skip);
    return EXIT_SUCCESS;
}
