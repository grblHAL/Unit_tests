#include "support/flow_program_host.h"
int main(void)
{
    CHECK(run_flow_program("#100=0\n#101=0\nO10DO\n#100=[#100+1]\n#101=[#101+1]\nO10WHILE[#100LT3]\n#102=7\n") == Status_OK);
    NEAR(flow_program_parameter(100), 3);
    NEAR(flow_program_parameter(101), 3);
    NEAR(flow_program_parameter(102), 7);
    return EXIT_SUCCESS;
}
