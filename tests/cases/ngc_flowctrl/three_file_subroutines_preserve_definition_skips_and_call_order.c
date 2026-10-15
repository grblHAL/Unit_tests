#include "support/flow_program_host.h"
int main(void)
{
    CHECK(run_flow_program(
        "#100=0\n"
        "O10SUB\n#100=[#100*10+1]\nO10ENDSUB\n"
        "O20SUB\n#100=[#100*10+2]\nO20ENDSUB\n"
        "O30SUB\n#100=[#100*10+3]\nO30ENDSUB\n"
        "O30CALL\nO10CALL\nO20CALL\n") == Status_OK);
    NEAR(flow_program_parameter(100), 312);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
