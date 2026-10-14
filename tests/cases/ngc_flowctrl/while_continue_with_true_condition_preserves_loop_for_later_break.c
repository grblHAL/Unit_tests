#include "support/flow_program_host.h"
int main(void)
{
    CHECK(run_flow_program("#100=0\n#101=0\nO10WHILE[#100LT3]\n#100=[#100+1]\nO20IF[#100EQ2]\nO10BREAK\nO20ENDIF\nO10CONTINUE\n#101=99\nO10ENDWHILE\n#102=7\n") == Status_OK);
    NEAR(flow_program_parameter(100), 2);
    NEAR(flow_program_parameter(101), 0);
    NEAR(flow_program_parameter(102), 7);
    return EXIT_SUCCESS;
}
