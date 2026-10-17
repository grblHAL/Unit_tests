#include "support/flow_program_host.h"
int main(void)
{
    CHECK(run_flow_program("#100=0\n#101=20\nO[#101]WHILE[#100LT3]\n#100=[#100+1]\nO20ENDWHILE\n#102=9\n") == Status_OK);
    NEAR(flow_program_parameter(100), 3);
    NEAR(flow_program_parameter(101), 20);
    NEAR(flow_program_parameter(102), 9);
    return EXIT_SUCCESS;
}
