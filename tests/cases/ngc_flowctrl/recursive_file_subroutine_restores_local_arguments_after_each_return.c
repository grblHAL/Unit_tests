#include "support/flow_program_host.h"

int main(void)
{
    CHECK(run_flow_program(
        "#1=99\n#100=0\n"
        "O10SUB\n#100=[#100+1]\nO20IF[#1GT0]\nO10CALL[#1-1]\nO20ENDIF\nO10ENDSUB\n"
        "O10CALL[3]\n#101=7\n") == Status_OK);
    NEAR(flow_program_parameter(100), 4);
    NEAR(flow_program_parameter(1), 99);
    NEAR(flow_program_parameter(101), 7);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
