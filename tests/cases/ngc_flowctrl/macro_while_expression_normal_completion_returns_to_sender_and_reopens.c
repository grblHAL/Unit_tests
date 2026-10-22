#include "support/macro_while_allocation_host.h"
int main(void)
{
    inject_while_failure = false;
    run_while_allocation_protocol();
    CHECK(failed_malloc_calls == 0 && arm_comments == 2);
    NEAR(ram_flow_parameter(1), 99);
    NEAR(ram_flow_parameter(100), 4);
    NEAR(ram_flow_parameter(101), 7);
    return EXIT_SUCCESS;
}
