#include "support/flow_program_host.h"

int main(void)
{
    CHECK(run_flow_program(
        "#1=99\n#100=0\n"
        "O10SUB\n#100=[#100+#1]\nO20CALL[4]\n#102=#1\nO10ENDSUB\n"
        "O20SUB\n#100=[#100+#1]\nO30CALL[5]\n#103=#1\nO20ENDSUB\n"
        "O30SUB\n#100=[#100+#1]\nO30ENDSUB\n"
        "O10CALL[3]\n#101=7\n") == Status_OK);
    NEAR(flow_program_parameter(100), 12);
    NEAR(flow_program_parameter(102), 3);
    NEAR(flow_program_parameter(103), 4);
    NEAR(flow_program_parameter(1), 99);
    NEAR(flow_program_parameter(101), 7);
    CHECK(ngc_call_level() == 0);
    return EXIT_SUCCESS;
}
