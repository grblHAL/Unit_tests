#include "support/flow_program_host.h"
int main(void)
{
    CHECK(run_flow_program("#100=0\nO10IF[1]\nO10BREAK\n#100=88\nO10ENDIF\n") == Status_FlowControlSyntaxError);
    NEAR(flow_program_parameter(100), 0);
    return EXIT_SUCCESS;
}
