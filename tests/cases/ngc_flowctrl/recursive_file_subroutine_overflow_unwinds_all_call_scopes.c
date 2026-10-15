#include "support/flow_program_host.h"

int main(void)
{
    CHECK(run_flow_program(
        "#1=99\n"
        "O10SUB\nO20IF[#1GT0]\nO10CALL[#1-1]\nO20ENDIF\nO10ENDSUB\n"
        "O10CALL[11]\n") == Status_FlowControlStackOverflow);
    CHECK(ngc_call_level() == 0);
    NEAR(flow_program_parameter(1), 99);
    return EXIT_SUCCESS;
}
