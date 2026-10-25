#include "support/flow_program_host.h"
int main(void)
{
    CHECK(run_flow_program("#100=0\nO10WHILE[1]\nO99CONTINUE\n#100=88\nO10ENDWHILE\n") == Status_FlowControlSyntaxError);
    NEAR(flow_program_parameter(100), 0);
    CHECK(ngc_call_level() == 0 && !gc_state.skip_blocks);
    return EXIT_SUCCESS;
}
