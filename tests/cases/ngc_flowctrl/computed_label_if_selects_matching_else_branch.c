#include "support/flow_program_host.h"
int main(void)
{
    CHECK(run_flow_program("#100=0\nO[10+2]IF[0]\n#100=99\nO[6*2]ELSE\n#100=7\nO[12]ENDIF\n#101=8\n") == Status_OK);
    NEAR(flow_program_parameter(100), 7);
    NEAR(flow_program_parameter(101), 8);
    return EXIT_SUCCESS;
}
