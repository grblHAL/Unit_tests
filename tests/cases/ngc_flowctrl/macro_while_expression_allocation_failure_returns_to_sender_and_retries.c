#include "support/macro_while_allocation_host.h"
int main(void)
{
    ram_expected_root_status = Status_FlowControlOutOfMemory;
    run_while_allocation_protocol();
    CHECK(failed_malloc_calls == 1 && arm_comments == 2);
    NEAR(ram_flow_parameter(1), 99);
    NEAR(ram_flow_parameter(100), 2);
    NEAR(ram_flow_parameter(101), 0);
    return EXIT_SUCCESS;
}
